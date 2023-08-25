#pragma once

#include <sparta/simulation/Unit.hpp>
#include "Inst.hpp"
#include "SimpleTLB.hpp"
#include "MemoryAccessInfo.hpp"

namespace olympia {

    class MMU : public sparta::Unit {

    public:
        class MMUParameterSet : public sparta::ParameterSet {
        public:
            MMUParameterSet(sparta::TreeNode *n) : sparta::ParameterSet(n) {}

            // Parameters for the TLB cache
            PARAMETER(bool, tlb_always_hit, false, "L1 TLB will always hit")
            PARAMETER(uint32_t, mmu_latency, 1, "Latency to mmu lookup")
        };


        MMU(sparta::TreeNode *node, const MMUParameterSet *p);

        bool memLookup(const MemoryAccessInfoPtr &mem_access_info_ptr);

        void setTLB(SimpleTLB &tlb);

        void reloadTLB_(uint64_t vaddr);


        static const char name[];
        SimpleTLB *tlb_cache_ = nullptr;
        const bool tlb_always_hit_;
        // Keep track of the instruction that causes current outstanding TLB miss
        InstPtr mmu_pending_inst_ptr_ = nullptr;
        // MMU latency parameter
        const uint32_t mmu_latency_;

        using MemoryAccessInfoPtr = sparta::SpartaSharedPointer<MemoryAccessInfo>;


        sparta::Counter tlb_hits_{
                getStatisticSet(), "tlb_hits",
                "Number of TLB hits", sparta::Counter::COUNT_NORMAL
        };
        sparta::Counter tlb_misses_{
                getStatisticSet(), "tlb_misses",
                "Number of TLB misses", sparta::Counter::COUNT_NORMAL
        };
    };
}