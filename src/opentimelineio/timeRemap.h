// SPDX-License-Identifier: Apache-2.0
// Copyright Contributors to the OpenTimelineIO project

#pragma once

#include "opentimelineio/timeEffect.h"

#include "opentime/timeMap.h"
#include "opentimelineio/anyDictionary.h"
#include "opentimelineio/serializableObject.h"
#include "opentimelineio/version.h"

#include <string>


namespace opentimelineio { namespace OPENTIMELINEIO_VERSION_NS {

OTIO_API_TYPE class TimeRemap : public TimeEffect
{
public:
    struct Schema {
        static auto constexpr name   = "TimeRemap";
        static int constexpr version = 1;
    };

    using Parent = TimeEffect;

    TimeRemap(
            const std::string& name = std::string(),
            const std::string& effect_name = std::string(),
            const TimeMap& time_map = TimeMap(),
            const AnyDictionary& metadata = AnyDictionary()) :
        Parent(name, effect_name, metadata),
        _time_map(time_map)
    {
    }

    void set_time_map(const TimeMap& time_map) {
        _time_map = time_map;
    }

    const TimeMap& time_map() const {
        return _time_map;
    }

protected:
    ~TimeRemap() override = default;

    bool read_from(Reader& reader) override {
        return (
            reader.read("time_map", &_time_map) &&
            Parent::read_from(reader));
    }

    void write_to(Writer& writer) const override {
        Parent::write_to(writer);
        writer.write("time_map", _time_map);
    }

private:
    TimeMap _time_map;
};


}} // namespace opentimelineio::OPENTIMELINEIO_VERSION_NS
