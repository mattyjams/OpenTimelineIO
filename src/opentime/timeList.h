// SPDX-License-Identifier: Apache-2.0
// Copyright Contributors to the OpenTimelineIO project

#pragma once

#include "opentime/export.h"
#include "opentime/rationalTime.h"
#include "opentime/timeRange.h"
#include "opentime/version.h"

#include <algorithm>
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

    void set_times(const std::vector<double>& times) {
        _times = times;
    }

    const std::vector<double>& times() const {
        return _times;
    }

    void set_rate(const double rate) {
        _rate = rate;
    }

    double rate() const {
        return _rate;
    }

    size_t size() const {
        return _times.size();
    }

    TimeRange range() const {
        if (_times.empty()) {
            return TimeRange();
        }

        const auto min_max =
            std::minmax_element(_times.cbegin(), _times.cend());

        const RationalTime start_time(*min_max.first, _rate);
        const RationalTime end_time_exclusive(*min_max.second + 1.0, _rate);

        return TimeRange::range_from_start_end_time(
            start_time, end_time_exclusive);
    }

    static TimeList list_from_range(const TimeRange& range) {
        const RationalTime duration = range.duration();
        const RationalTime start_time = range.start_time().rescaled_to(duration);

        if (duration.value() <= 0.0) {
            return TimeList({start_time.value()}, start_time.rate());
        }

        const RationalTime end_time_exclusive = range.end_time_exclusive();

        const RationalTime stepTime(1.0, duration.rate());

        std::vector<double> times;
        RationalTime current_time = start_time;
        while (current_time < end_time_exclusive) {
            times.push_back(current_time.value());
            current_time += stepTime;
        }

        return TimeList(times, duration.rate());
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
