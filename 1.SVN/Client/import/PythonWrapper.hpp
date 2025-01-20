/**
 * ? @file PythonWrapper.hpp
 * ! @author LWT
 */
#ifndef PYTHONWRAPPER_HPP
#define PYTHONWRAPPER_HPP

#include "stdafx.h"

#include <variant>
#include <vector>
#include <memory>

namespace pythonwrapper {

/**
 * @brief Python object types
 */
enum class PythonObjectType : uint8_t {
    List,
    Tuple,
    Dict,
};

class IPythonObject {
  public:
    /**
     * @brief Construct a new IPythonObject object
     *
     */
    IPythonObject() = default;

    /**
     * @brief Copy constructor
     *
     */
    IPythonObject(const IPythonObject&) = delete;

    /**
     * @brief Copy assignment operator
     *
     */

    IPythonObject& operator=(const IPythonObject&) = delete;

    /**
     * @brief Destroy the IPythonObject object
     *
     */
    virtual ~IPythonObject() = default;

    /**
     * @brief Create Python object
     *
     * @return PyObject* Python object
     */
    [[nodiscard]] virtual PyObject* create() const noexcept = 0;
};

class ListFactory final : public IPythonObject {
  public:
    /**
     * @brief Create Python object
     *
     * @return PyObject* Python object
     */
    [[nodiscard]] PyObject* create() const noexcept override
    {
        return PyList_New(0);
    }
};

class TupleFactory final : public IPythonObject {
  public:
    /**
     * @brief Create Python object
     *
     * @return PyObject* Python object
     */
    [[nodiscard]] PyObject* create() const noexcept override
    {
        return PyTuple_New(0);
    }
};

class DictFactory final : public IPythonObject {
  public:
    /**
     * @brief Create Python object
     *
     * @return PyObject* Python object
     */
    [[nodiscard]] PyObject* create() const noexcept override
    {
        return PyDict_New();
    }
};

class PythonObjectFactoryCreator {
  public:
    /**
     * @brief Create Python object factory
     *
     * @param type Python object type
     */
    static std::unique_ptr<IPythonObject> create_py_object_factory(const PythonObjectType type)
    {
        switch (type)
        {
        case PythonObjectType::List:
            return std::make_unique<ListFactory>();
        case PythonObjectType::Tuple:
            return std::make_unique<TupleFactory>();
        case PythonObjectType::Dict:
            return std::make_unique<DictFactory>();
        }
        return std::make_unique<ListFactory>();
    }
};

/**
 * @brief Convert Python object type to Python type
 *
 * @param obj_type Python object type
 */
inline PyObject* object_type_to_py_type(const PythonObjectType obj_type) noexcept
{
    switch (obj_type)
    {
    case PythonObjectType::List:
        return PyList_New(0);
    case PythonObjectType::Tuple:
        return PyTuple_New(0);
    case PythonObjectType::Dict:
        return PyDict_New();
    }
    return nullptr;
}

/**
 * @brief Variant type for storing different types of values in a single object
 */
using value_type_t = std::
    variant<int, unsigned, long, unsigned long, unsigned long long, double, float, const char*, std::string, PyObject*>;

class PythonObjectBuilder {
  public:
    /**
     * @brief Construct a new Python Object Builder object
     *
     * @param type Python object type
     */
    explicit PythonObjectBuilder(const PythonObjectType type)
        : m_p_factory{PythonObjectFactoryCreator::create_py_object_factory(type)}
    {
    }

    /**
     * @brief Destroy the Python Object Builder object
     */
    ~PythonObjectBuilder()
    {
        for (auto& value: m_values)
        {
            std::visit(
                []<typename T0>(T0& v)
                {
                    if constexpr (std::is_same_v<T0, PyObject*>) { Py_XDECREF(v); }
                },
                value);
        }
    }

    PythonObjectBuilder(const PythonObjectBuilder&) = delete;
    PythonObjectBuilder& operator=(const PythonObjectBuilder&) = delete;

    /**
     * @brief Add a value to the Python object
     *
     * @param value Value to add
     */
    PythonObjectBuilder& add_item(const value_type_t& value)
    {
        m_values.emplace_back(value);

        return *this;
    }

    /**
     * @brief Build the Python object
     *
     * @return PyObject* Python object
     */
    [[nodiscard]] PyObject* build() const
    {
        PyObject* obj{m_p_factory->create()};
        if (nullptr == obj) { return nullptr; }

        for (const auto& value: m_values)
        {
            PyObject* py_obj{std::visit(
                [this](const auto& v)
                {
                    return create_object(v);
                },
                value)};

            if (py_obj != nullptr)
            {
                if (PyList_Check(obj)) { PyList_Append(obj, py_obj); }
                else if (PyTuple_Check(obj)) { PyTuple_SetItem(obj, PyTuple_Size(obj), py_obj); }
                else if (PyDict_Check(obj)) { PyDict_SetItem(obj, py_obj, py_obj); }
            }
        }

        return obj;
    }

  private:
    /**
     * @brief Create Python object from C++ object
     *
     * @tparam T Type of the object
     */
    template<typename T>
    [[nodiscard]] PyObject* create_object(const T& value) const
    {
        if constexpr (std::is_same_v<T, int>) { return PyLong_FromLong(value); }
        else if constexpr (std::is_same_v<T, unsigned>) { return PyLong_FromUnsignedLong(value); }
        else if constexpr (std::is_same_v<T, long>) { return PyLong_FromLong(value); }
        else if constexpr (std::is_same_v<T, unsigned long>) { return PyLong_FromUnsignedLong(value); }
        else if constexpr (std::is_same_v<T, unsigned long long>) { return PyLong_FromUnsignedLongLong(value); }
        else if constexpr (std::is_same_v<T, double>) { return PyFloat_FromDouble(value); }
        else if constexpr (std::is_same_v<T, float>) { return PyFloat_FromDouble(value); }
        else if constexpr (std::is_same_v<T, const char*>) { return PyUnicode_FromString(value); }
        else if constexpr (std::is_same_v<T, std::string>) { return PyUnicode_FromString(value.c_str()); }
        else if constexpr (std::is_same_v<T, PyObject*>)
        {
            Py_INCREF(value); // increment reference count
            return value;
        }
        return nullptr;

    }

    /**
     * @brief Python object type
     */
    std::unique_ptr<IPythonObject> m_p_factory{};

    /**
     * @brief Values to add to the Python object
     */
    std::vector<value_type_t> m_values{};
};

/**
 * @brief Print Python object
 *
 * @param obj Python object
 */
inline void print_python_object(PyObject* obj)
{
    if (PyList_Check(obj))
    {
        const Py_ssize_t size = PyList_Size(obj);
        for (Py_ssize_t i = 0; i < size; ++i)
        {
            if (auto* item{PyList_GetItem(obj, i)}; PyLong_Check(item)) { TraceError("int: %ld", PyLong_AsLong(item)); }
            else if (PyFloat_Check(item)) { TraceError("float: %f", PyFloat_AsDouble(item)); }
            else if (PyUnicode_Check(item))
            {
                PyObject* repr = PyObject_Repr(item);
                const char* str = PyString_AsString(repr);
                TraceError("String: %s", str);
                Py_XDECREF(repr);
            }
            else if (PyBytes_Check(item)) { TraceError("bytes: %s", PyBytes_AsString(item)); }
            else if (PyDict_Check(item))
            {
                PyObject* keys = PyDict_Keys(item);
                PyObject* values = PyDict_Values(item);
                PyObject* items = PyDict_Items(item);

                PyObject* repr_keys = PyObject_Repr(keys);
                PyObject* repr_values = PyObject_Repr(values);
                PyObject* repr_items = PyObject_Repr(items);

                const char* str_keys = PyString_AsString(repr_keys);
                const char* str_values = PyString_AsString(repr_values);
                const char* str_items = PyString_AsString(repr_items);

                TraceError("Keys: %s", str_keys);
                TraceError("Values: %s", str_values);
                TraceError("Items: %s", str_items);

                Py_XDECREF(keys);
                Py_XDECREF(values);
                Py_XDECREF(items);

                Py_XDECREF(repr_keys);
                Py_XDECREF(repr_values);
                Py_XDECREF(repr_items);
            }
            else if (PyTuple_Check(item))
            {
                PyObject* repr = PyObject_Repr(item);
                const char* str = PyString_AsString(repr);
                TraceError("Tuple: %s", str);
                Py_XDECREF(repr);
                ;
            }
            else if (PyList_Check(item))
            {
                // print elements
                PyObject* repr = PyObject_Repr(item);
                const char* str = PyString_AsString(repr);
                TraceError("List: %s", str);
                Py_XDECREF(repr);
            }
            else { TraceError("unknown"); }
        }
    }
    else { TraceError("not a list"); }
}

} // namespace pythonwrapper

#endif // PYTHONWRAPPER_HPP
