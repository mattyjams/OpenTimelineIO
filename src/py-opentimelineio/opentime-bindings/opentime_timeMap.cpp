// SPDX-License-Identifier: Apache-2.0
// Copyright Contributors to the OpenTimelineIO project

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "opentime_bindings.h"
#include "opentime/timeList.h"
#include "opentime/timeMap.h"
#include "opentime/stringPrintf.h"

namespace py = pybind11;
using namespace pybind11::literals;
using namespace opentime;


void opentime_timeMap_bindings(py::module m)
{
    py::class_<TimeMap>(m, "TimeMap")
        .def(py::init<TimeList, TimeList>(),
             "input_times"_a = TimeList(), "output_times"_a = TimeList())
        .def_property_readonly("input_times", &TimeMap::input_times)
        .def_property_readonly("output_times", &TimeMap::output_times)
        .def("__copy__", [](const TimeMap& tm) {
                return tm;
            })
        .def("__deepcopy__", [](const TimeMap& tm) {
                return tm;
            })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__str__", [](const TimeMap& tm) {
                return string_printf(
                    "TimeMap(%s, %s)",
                    opentime_python_str(tm.input_times()).c_str(),
                    opentime_python_str(tm.output_times()).c_str());
            })
        .def("__repr__", [](const TimeMap& tm) {
            return string_printf(
                "otio.opentime.TimeMap(input_times=%s, output_times=%s)",
                opentime_python_repr(tm.input_times()).c_str(),
                opentime_python_repr(tm.output_times()).c_str());
            })
        ;
}
