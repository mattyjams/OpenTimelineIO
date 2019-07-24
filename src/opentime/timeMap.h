// SPDX-License-Identifier: Apache-2.0
// Copyright Contributors to the OpenTimelineIO project

#pragma once

#include "opentime/export.h"
#include "opentime/errorStatus.h"
#include "opentime/timeList.h"
#include "opentime/version.h"


namespace opentime { namespace OPENTIME_VERSION_NS {


OPENTIME_API_TYPE class TimeMap
{
public:
    explicit TimeMap(
            const TimeList& input_times = TimeList(),
            const TimeList& output_times = TimeList())
    {
        ErrorStatus error_status;
        set_times(input_times, output_times, &error_status);
        if (is_error(error_status)) {
            // XXX: Emit an error here somehow?
        }
    }

    void set_times(
            const TimeList& input_times,
            const TimeList& output_times,
            ErrorStatus* error_status) {
        if (input_times.size() != output_times.size()) {
            if (error_status) {
                *error_status =
                    ErrorStatus(
                        ErrorStatus::VALUE_COUNT_MISMATCH,
                        "input and output time lists must contain "
                        "the same number of values");
            }
            return;
        }

        _input_times = input_times;
        _output_times = output_times;
    }

    const TimeList& input_times() const {
        return _input_times;
    }

    const TimeList& output_times() const {
        return _output_times;
    }

    TimeMap(const TimeMap&) = default;
    TimeMap& operator=(const TimeMap&) = default;

    bool operator==(const TimeMap& other) const {
        return (
            _input_times == other._input_times &&
            _output_times == other._output_times);
    }

    bool operator!=(const TimeMap& other) const {
        return !(*this == other);
    }

private:
    TimeList _input_times;
    TimeList _output_times;
};


}} // namespace opentime::OPENTIME_VERSION_NS
