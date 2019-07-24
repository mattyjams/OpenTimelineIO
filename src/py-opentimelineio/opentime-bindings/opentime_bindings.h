// SPDX-License-Identifier: Apache-2.0
// Copyright Contributors to the OpenTimelineIO project

#ifndef OTIO_OPENTIME_BINDINGS_H
#define OTIO_OPENTIME_BINDINGS_H

#include "opentime/rationalTime.h"
#include "opentime/timeList.h"
#include <pybind11/pybind11.h>
#include <string>

void opentime_rationalTime_bindings(pybind11::module);
void opentime_timeList_bindings(pybind11::module);
void opentime_timeMap_bindings(pybind11::module);
void opentime_timeRange_bindings(pybind11::module);
void opentime_timeTransform_bindings(pybind11::module);

std::string opentime_python_str(opentime::RationalTime rt);
std::string opentime_python_repr(opentime::RationalTime rt);

std::string opentime_python_str(const opentime::TimeList& tl);
std::string opentime_python_repr(const opentime::TimeList& tl);

#endif
