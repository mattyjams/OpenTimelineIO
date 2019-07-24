// SPDX-License-Identifier: Apache-2.0
// Copyright Contributors to the OpenTimelineIO project

#pragma once

#include "opentime/export.h"
#include "opentime/version.h"

#include <vector>


namespace opentime { namespace OPENTIME_VERSION_NS {


OPENTIME_API_TYPE class TimeList
{
public:
    explicit TimeList(
            const std::vector<double>& times = std::vector<double>(),
            const double rate = 1.0) :
        _times(times),
        _rate(rate)
    {
    }

    const std::vector<double>& times() const {
        return _times;
    }

    double rate() const {
        return _rate;
    }

    size_t size() const {
        return _times.size();
    }

    TimeList(const TimeList&) = default;
    TimeList& operator=(const TimeList&) = default;

    bool operator==(const TimeList& other) const {
        return _times == other._times && _rate == other._rate;
    }

    bool operator!=(const TimeList& other) const {
        return !(*this == other);
    }

private:
    std::vector<double> _times;
    double _rate;
};


}} // namespace opentime::OPENTIME_VERSION_NS
