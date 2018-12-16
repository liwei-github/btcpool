/*
 The MIT License (MIT)

 Copyright (c) [2018] [BTC.COM]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "StatisticsDecred.h"
#include "StratumDecred.h"

template <>
void ShareStatsDay<ShareDecred<NetworkTraitsDecred>>::processShare(uint32_t hourIdx, const ShareDecred<NetworkTraitsDecred> &share) {
  ScopeLock sl(lock_);

  if (StratumStatus::isAccepted(share.status())) {
    shareAccept1h_[hourIdx] += share.sharediff();
    shareAccept1d_          += share.sharediff();

    double score = share.score();
    double reward = NetworkTraitsDecred::GetBlockRewardShare(share.height(), static_cast<NetworkDecred>(share.network()));
    double earn = score * reward;

    score1h_[hourIdx] += score;
    score1d_          += score;
    earn1h_[hourIdx]  += earn;
    earn1d_           += earn;

  } else {
    shareReject1h_[hourIdx] += share.sharediff();
    shareReject1d_          += share.sharediff();
  }
  modifyHoursFlag_ |= (0x01u << hourIdx);
}

template <>
void ShareStatsDay<ShareDecred<NetworkTraitsHcash>>::processShare(uint32_t hourIdx, const ShareDecred<NetworkTraitsHcash> &share) {
  ScopeLock sl(lock_);

  if (StratumStatus::isAccepted(share.status())) {
    shareAccept1h_[hourIdx] += share.sharediff();
    shareAccept1d_          += share.sharediff();

    double score = share.score();
    double reward = NetworkTraitsHcash::GetBlockRewardShare(share.height(), static_cast<NetworkDecred>(share.network()));
    double earn = score * reward;

    score1h_[hourIdx] += score;
    score1d_          += score;
    earn1h_[hourIdx]  += earn;
    earn1d_           += earn;

  } else {
    shareReject1h_[hourIdx] += share.sharediff();
    shareReject1d_          += share.sharediff();
  }
  modifyHoursFlag_ |= (0x01u << hourIdx);
}

///////////////  template instantiation ///////////////
template class ShareStatsDay<ShareDecred<NetworkTraitsDecred>>;
template class ShareStatsDay<ShareDecred<NetworkTraitsHcash>>;
