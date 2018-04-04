//
// RapMap - Rapid and accurate mapping of short reads to transcriptomes using
// quasi-mapping.
// Copyright (C) 2015, 2016 Rob Patro, Avi Srivastava, Hirak Sarkar
//
// This file is part of RapMap.
//
// RapMap is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RapMap is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RapMap.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __HIT_MANAGER_HPP__
#define __HIT_MANAGER_HPP__

#include "RapMapUtils.hpp"
//#include "RapMapIndex.hpp"
#include "RapMapSAIndex.hpp"

//#include "eytzinger_array.h"

#include <tuple>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

namespace rapmap {
    namespace hit_manager {
        using HitInfo = rapmap::utils::HitInfo;
        using ProcessedHit = rapmap::utils::ProcessedHit;
        using MateStatus = rapmap::utils::MateStatus;
        using PositionListHelper = rapmap::utils::PositionListHelper;
        using QuasiAlignment = rapmap::utils::QuasiAlignment;
        using TxpQueryPos = rapmap::utils::TxpQueryPos;
        using SATxpQueryPos = rapmap::utils::SATxpQueryPos;

        template <typename T>
        using SAIntervalHit = rapmap::utils::SAIntervalHit<T>;
        using SAHitMap = std::map<int, rapmap::utils::ProcessedSAHit>;
        using ProcessedSAHit = rapmap::utils::ProcessedSAHit;

        class SAProcessedHitVec {
            public:
                std::vector<ProcessedSAHit> hits;
                std::vector<uint32_t> txps;
        };
        /*
        using SAProcessedHitVec = std::tuple<std::vector<ProcessedSAHit>, std::vector<uint32_t>>;
        */

        // Return hits from processedHits where position constraints
        // match maxDist
        bool collectHitsSimple(std::vector<ProcessedHit>& processedHits,
                uint32_t readLen,
                uint32_t maxDist,
                std::vector<QuasiAlignment>& hits,
                MateStatus mateStatus);

        // Return hits from processedHits where position constraints
        // match maxDist
        bool collectHitsSimpleSA(SAHitMap& processedHits,
                uint32_t readLen,
                uint32_t maxDist,
                std::vector<QuasiAlignment>& hits,
                MateStatus mateStatus);

        // Return hits from processedHits where position constraints
        // match maxDist
        bool collectHitsSimpleSA2(std::vector<ProcessedSAHit>& processedHits,
                uint32_t readLen,
                uint32_t maxDist,
                std::vector<QuasiAlignment>& hits,
                MateStatus mateStatus);


        // Intersects the hit h2 with outHits.
        // This will modify outHits so that the tqvec field of the
        // entries in outHits that are labeled by the transcripts in
        // which h2 appears will have an iterator to the beginning of
        // the position list for h2.
        //void intersectWithOutput(HitInfo& h2, RapMapIndex& rmi,
        //        std::vector<ProcessedHit>& outHits);

        template <typename RapMapIndexT>
        void intersectSAIntervalWithOutput(SAIntervalHit<typename RapMapIndexT::IndexType>& h,
                                           RapMapIndexT& rmi,
                                           uint32_t intervalCounter,
                                           SAHitMap& outHits);
                                           

        template <typename RapMapIndexT>
        void intersectSAIntervalWithOutput2(SAIntervalHit<typename RapMapIndexT::IndexType>& h,
                RapMapIndexT& rmi,
                SAProcessedHitVec& outStructs);

        /*
        void intersectSAIntervalWithOutput3(SAIntervalHit& h,
                RapMapSAIndex& rmi,
                SAProcessedHitVec& outHits);
                */

        //std::vector<ProcessedHit> intersectHits(
        //        std::vector<HitInfo>& inHits,
         //       RapMapIndex& rmi);

        template <typename RapMapIndexT>
        SAHitMap intersectSAHits(
                                 std::vector<SAIntervalHit<typename RapMapIndexT::IndexType>>& inHits,
                                 RapMapIndexT& rmi, 
                                 size_t readLen,
                                 bool strictFilter=false);

        template <typename RapMapIndexT>
        std::vector<ProcessedSAHit> intersectSAHits2(
                std::vector<SAIntervalHit<typename RapMapIndexT::IndexType>>& inHits,
                RapMapIndexT& rmi);
    }
}


#endif // __HIT_MANAGER_HPP__
