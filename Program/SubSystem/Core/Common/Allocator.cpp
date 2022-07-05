/**
* @file    Tools.h
* @brief   �֗��֐�
*
* @date	   2022/06/25 2022�N�x����
*/


#include "Allocator.h"

struct TLSFMemoryHeader
{
    uint32_t memorySize;
    bool isUse;
    BoundaryBlock* prev;
    BoundaryBlock* next;

    TLSFMemoryHeader() : memorySize(0), isUse(false), prev(nullptr), next(nullptr)
    {
    }
};

class BoundaryBlock
{
    using Hader = TLSFMemoryHeader;
    using EndTag = uint32_t;
public:
    Hader m_header;

public:

    BoundaryBlock(uint32_t size) {
        m_header.memorySize = size;
        WriteEndTag();
    }

    void* GetPointer() {
        return reinterpret_cast<void*>(reinterpret_cast<char*>(this) + sizeof(BoundaryBlock));
    }

    uint32_t GetMemorySize() const {
        return m_header.memorySize;
    }

    uint32_t GetBlockSize() const {
        return sizeof(BoundaryBlock) + GetMemorySize() + GetEndTagSize();
    }

    BoundaryBlock* Prev() {
        uint32_t* preSize = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) - GetEndTagSize());
        return reinterpret_cast<BoundaryBlock*>(reinterpret_cast<char*>(this) - *preSize);
    }

    BoundaryBlock* Next() {
        return reinterpret_cast<BoundaryBlock*>(reinterpret_cast<char*>(this) + GetBlockSize());
    }

    void Marge() {
        const uint32_t newSize = GetBlockSize() + Next()->GetMemorySize();
        m_header.memorySize = newSize;
        WriteEndTag();
    }

    BoundaryBlock* Split(uint32_t size) {
        const uint32_t splitBlockSize = sizeof(BoundaryBlock) + size + GetEndTagSize();
        if (splitBlockSize > GetMemorySize())
            return nullptr;

        const uint32_t newNextSize = GetMemorySize() - splitBlockSize;

        m_header.memorySize = size;
        WriteEndTag();

        BoundaryBlock* next = Next();
        new (next) BoundaryBlock(newNextSize);
        return next;
    }

    bool EnableSplit(uint32_t size) const {
        return sizeof(BoundaryBlock) + size + GetEndTagSize() <= GetMemorySize();
    }

private:

    uint32_t GetEndTagSize() const {
        return sizeof(EndTag);
    }

    void WriteEndTag() {
        new(reinterpret_cast<char*>(Next()) - GetEndTagSize()) EndTag(GetBlockSize());
    }
};

void Allocator::Initialize()
{
    m_numOfDivisions = powf(2, N);

    uint32_t memorySize = 0x100000;
    m_memory = malloc(memorySize);

    BoundaryBlock* block = new (m_memory) BoundaryBlock(memorySize - (sizeof(TLSFMemoryHeader) + sizeof(uint32_t)));

    const uint32_t fli = GetMsb(block->GetMemorySize());
    const uint32_t sli = GetSecondCategory(block->GetMemorySize(), fli);

    // SLI �̃��X�g�L����ێ�����r�b�g�z��̐���
    const uint32_t maxBitSize = fli + 1;
    m_freeListBits.resize(maxBitSize);

    // �t���[���X�g�z�񐶐�
    const uint32_t maxListSize = fli * powf(2, N) + sli + 1;
    m_freeLists.resize(maxListSize);

    AddToFreeList(block);
}

Allocator::~Allocator()
{
    free(m_memory);
    m_memory = nullptr;
}

void* Allocator::Allocate(uint32_t size) noexcept
{
    const uint32_t fli = GetMsb(size);
    const uint32_t sli = GetSecondCategory(size, fli);

    BoundaryBlock* block = GetFreeList(fli, sli);

    // Allocate�����f�[�^�����X�i�[�������
    RemoveFromFreeList(block);

    // ���������c��̃f�[�^���t���[���X�g�ɒǉ�
    AddToFreeList(block->Split(size));

    return block->GetPointer();
}

void Allocator::Deallocate(void* ptr) noexcept
{
    BoundaryBlock* block = reinterpret_cast<BoundaryBlock*>(reinterpret_cast<char*>(ptr) - sizeof(BoundaryBlock));

    if (block == m_memory)
    {
        if (!(block->Next()->m_header.isUse))
        {
            RemoveFromFreeList(block->Next());
            block->Marge();
        }
    }
    else
    {
        if (!(block->Next()->m_header.isUse))
        {
            RemoveFromFreeList(block->Next());
            block->Marge();
        }
        if (!(block->Prev()->m_header.isUse))
        {
            RemoveFromFreeList(block->Prev());
            block->Prev()->Marge();
            block = block->Prev();
        }
    }

    AddToFreeList(block);
}

ulong Allocator::GetMsb(const uint32_t num) const noexcept
{
    ulong index = 0;
    _BitScanReverse(&index, num);
    return index;
}

ulong Allocator::GetLsb(const uint32_t num) const noexcept
{
    ulong index = 0;
    _BitScanForward(&index, num);
    return index;
}

ulong Allocator::GetSecondCategory(const uint32_t num, const uint32_t msb) const noexcept
{
    return (num & ((1 << msb) - 1)) >> (msb - N);
}

uint8_t Allocator::GetFreeListToCategory(const uint8_t bit, const uint32_t listBit) const noexcept
{
    // sli �ȏ�̒l�������Ă���}�X�N���g�p���ėL���� sli �𓱂�
    const uint32_t mask = 0xffffffff << bit;
    const uint32_t enableBit = listBit & mask;

    if (enableBit == 0)
    {
        return -1;
    }

    return GetLsb(enableBit);
}

BoundaryBlock* Allocator::GetFreeList(uint32_t fli, uint32_t sli) const noexcept
{
    uint32_t ret = 0;

    ret = GetFreeListToCategory(sli, m_freeListBits[fli]);
    if (ret != uint8_t(-1))
    {
        sli = ret;
    }
    else
    {
        ret = GetFreeListToCategory(fli, m_globalFLI);
        if (ret != uint8_t(-1))
        {
            fli = ret;
            sli = GetFreeListToCategory(sli, m_freeListBits[fli]);
        }
    }

    const uint32_t index = fli * m_numOfDivisions + sli;
    return m_freeLists[index];
}

void Allocator::AddToFreeList(BoundaryBlock* block) noexcept
{
    if (!block)
        return;

    block->m_header.isUse = false;

    const uint32_t fli = GetMsb(block->GetMemorySize());
    const uint32_t sli = GetSecondCategory(block->GetMemorySize(), fli);

    // FLI �̃��X�g�r�b�g�ɒǉ�
    m_globalFLI |= 1 << fli;

    // SLI �̃��X�g�r�b�g�ɒǉ�
    m_freeListBits[fli] |= 1 << sli;

    // �t���[���X�g�̐擪�ɒǉ�
    const uint32_t numList = fli * m_numOfDivisions + sli;
    if (m_freeLists[numList])
    {
        m_freeLists[numList]->m_header.prev = block;
        block->m_header.next = m_freeLists[numList];
        m_freeLists[numList] = block;
    }
    else
    {
        m_freeLists[numList] = block;
    }
}

void Allocator::RemoveFromFreeList(BoundaryBlock* block) noexcept
{
    if (!block)
        return;

    block->m_header.isUse = true;

    const auto prev = block->m_header.prev;
    const auto next = block->m_header.next;

    // �w�� Block �����Ԃ̏ꍇ
    if (prev && next)
    {
        prev->m_header.next = next;
        next->m_header.prev = prev;
    }

    // �w�� Block ���擪�̏ꍇ
    else if (next)
    {
        next->m_header.prev = nullptr;

        const uint32_t fli = GetMsb(block->GetMemorySize());
        const uint32_t sli = GetSecondCategory(block->GetMemorySize(), fli);

        const uint32_t index = fli * m_numOfDivisions + sli;
        m_freeLists[index] = prev;
    }

    // �w�� Block �����[�̏ꍇ
    else if (prev)
    {
        prev->m_header.next = nullptr;
    }

    // �w�� Block ��������̏ꍇ�A���X�g�������
    else
    {
        const uint32_t fli = GetMsb(block->GetMemorySize());
        const uint32_t sli = GetSecondCategory(block->GetMemorySize(), fli);

        // FLI �̃��X�g�r�b�g�̏���
        m_globalFLI ^= (1 << fli);

        // SLI �̃��X�g�r�b�g�ɏ���
        m_freeListBits[fli] ^= (1 << sli);

        const uint32_t index = fli * m_numOfDivisions + sli;
        m_freeLists[index] = nullptr;
    }
}