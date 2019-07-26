// SPDX-License-Identifier: Apache-2.0
// Copyright Contributors to the OpenTimelineIO project

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "opentime_bindings.h"
#include "opentime/timeList.h"
#include "opentime/stringPrintf.h"

#include <sstream>
#include <string>
#include <vector>

namespace py = pybind11;
using namespace pybind11::literals;
using namespace opentime;


static
std::string
_double_vector_to_string(const std::vector<double>& values)
{
    if (values.empty()) {
        return "[]";
    }

    std::ostringstream stream;
    stream << "[";

    auto iter = values.cbegin();
    stream << *iter;

    while (++iter != values.cend()) {
        stream << ", " << *iter;
    }

    stream << "]";

    return stream.str();
}

std::string
opentime_python_str(const opentime::TimeList& tl)
{
    return string_printf(
        "TimeList(%s, %g)",
        _double_vector_to_string(tl.times()).c_str(),
        tl.rate());
}

std::string
opentime_python_repr(const opentime::TimeList& tl)
{
    return string_printf(
        "otio.opentime.TimeList(times=%s, rate=%g)",
        _double_vector_to_string(tl.times()).c_str(),
        tl.rate());
}


void opentime_timeList_bindings(py::module m)
{
    py::class_<TimeList>(m, "TimeList")
        .def(py::init<std::vector<double>, double>(),
             "times"_a = std::vector<double>(), "rate"_a = 1.0)
        .def_property("times", &TimeList::times, &TimeList::set_times)
        .def_property("rate", &TimeList::rate, &TimeList::set_rate)
        .def_property_readonly("size", &TimeList::size)
        .def("range", &TimeList::range)
        .def_static("list_from_range", &TimeList::list_from_range, "range"_a)
        .def("__copy__", [](const TimeList& tl) {
                return tl;
            })
        .def("__deepcopy__", [](const TimeList& tl) {
                return tl;
            })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__str__", [](const TimeList& tl) {
                return opentime_python_str(tl);
            })
        .def("__repr__", [](const TimeList& tl) {
            return opentime_python_repr(tl);
            })
        ;
}
