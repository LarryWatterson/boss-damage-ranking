#ifndef CLIENT_PYTHONHELPER_HPP
#define CLIENT_PYTHONHELPER_HPP

#include "StdAfx.h"
#include <typeindex>

namespace py_helper
{
	class GarbageCollector
	{
	public:
		GarbageCollector() = default;
		~GarbageCollector() {
			for (auto ptr : m_vecGarbage) {
				try
				{
					Py_XDECREF(ptr);
				}
				catch (const std::exception& e)
				{
					TraceError("GarbageCollector::~GarbageCollector - %s", e.what());
				}
			} 
			m_vecGarbage.clear();
		}

		[[nodiscard]] auto GetGarbage() const {
			return m_vecGarbage;
		}

		auto addObject(PyObject* ptr) {
			return Register(ptr);
		}

		template<typename T>
		auto makeValue(const T& value) -> PyObject* {
			PyObject* pyValue = ConvertToPyObject(value);
			return Register(pyValue);
		}

		auto makeValue(const std::string& value) -> PyObject* {
			return Register(Py_BuildValue("s", value.c_str()));
		}

		auto makeDict() -> PyObject* {
			return Register(PyDict_New());
		}

		auto makeList() -> PyObject* {
			return Register(PyList_New(0));
		}

		auto makeTuple(const int size) -> PyObject* {
			return Register(PyTuple_New(size));
		}

	protected:
		PyObject* Register(PyObject* ptr) {
			m_vecGarbage.emplace_back(ptr);
			return ptr;
		}

	private:
		std::vector<PyObject*> m_vecGarbage;

		template <typename T>
		static PyObject* ConvertToPyObject(const T& value) {
			static const std::unordered_map<std::type_index, const char*> typeToFormat = {
				{ typeid(DWORD), "k" },
				{ typeid(WORD), "h" },
				{ typeid(int), "i" },
				{ typeid(unsigned int), "I" },
				{ typeid(BYTE), "B" },
				{ typeid(float), "f" },
				{ typeid(double), "d" },
				{ typeid(short), "h" },
				{ typeid(long), "i" },
				{ typeid(long long), "L" },
				{ typeid(unsigned long long), "K" },
				{ typeid(const char*), "s" },
				{ typeid(char*), "s" },
				{ typeid(std::string), "s" },
				{ typeid(bool), "b" },
				{ typeid(PyObject*), "O" }
			};

			const auto it = typeToFormat.find(typeid(T));
			if (it != typeToFormat.end()) {
				return Py_BuildValue(it->second, value);
			}
			// 
			TraceError("Unknown type: %s", typeid(T).name());
			return nullptr;
		}
	};

	class CPythonTuple : public GarbageCollector
	{
	public:
		explicit CPythonTuple(const int size) { m_tuple = makeTuple(size); }
		~CPythonTuple() = default;

		[[nodiscard]] auto GetTuple() const {
			return m_tuple;
		}

		auto SetItem(const int index, PyObject* value) const
		{
			Py_INCREF(value);
			if (PyTuple_SetItem(m_tuple, index, value) != 0) {
				PyErr_Print();
			}
		}

		auto printTuple() const
		{
			PyObject* repr = PyObject_Repr(m_tuple);
			const char* str = PyString_AsString(repr);
			TraceError("Tuple: %s", str);
			Py_XDECREF(repr);
		}

	private:
		PyObject* m_tuple;
	};

	class CPythonList : public GarbageCollector
	{
	public:
		CPythonList() { m_list = makeList(); }
		~CPythonList() = default;

		template <typename T>
		void Append(const T& value) {
			if (auto pyValue = makeValue(value)) {
				Py_INCREF(pyValue);
				if (PyList_Append(m_list, pyValue) != 0) {
					PyErr_Print();
				}
			}
			else {
				PyErr_Print();
			}
		}

		auto printList() const
		{
			PyObject* repr = PyObject_Repr(m_list);
			const char* str = PyString_AsString(repr);
			TraceError("List: %s", str);
			Py_XDECREF(repr);
		}

		[[nodiscard]] auto GetList() const {
			return m_list;
		}

	private:
		PyObject* m_list;
	};

	class CPythonDictionary : public GarbageCollector
	{
	public:
		CPythonDictionary() { m_dict = makeDict(); }
		~CPythonDictionary() = default;

		template <typename T>
		void SetItem(const std::string& key, const T& value) {
			if (auto pyValue = makeValue(value)) {
				Py_INCREF(pyValue);
				if (PyDict_SetItemString(m_dict, key.c_str(), pyValue) != 0) {
					PyErr_Print();
				}
			}
			else {
				PyErr_Print();
			}
		}

		auto printDict() const
		{
			PyObject* keys = PyDict_Keys(m_dict);
			PyObject* values = PyDict_Values(m_dict);
			PyObject* items = PyDict_Items(m_dict);

			PyObject* reprKeys = PyObject_Repr(keys);
			PyObject* reprValues = PyObject_Repr(values);
			PyObject* reprItems = PyObject_Repr(items);

			const char* strKeys = PyString_AsString(reprKeys);
			const char* strValues = PyString_AsString(reprValues);
			const char* strItems = PyString_AsString(reprItems);

			TraceError("Keys: %s", strKeys);
			TraceError("Values: %s", strValues);
			TraceError("Items: %s", strItems);

			Py_XDECREF(keys);
			Py_XDECREF(values);
			Py_XDECREF(items);

			Py_XDECREF(reprKeys);
			Py_XDECREF(reprValues);
			Py_XDECREF(reprItems);
		}

		[[nodiscard]] auto GetDict() const {
			return m_dict;
		}

	private:
		PyObject* m_dict;
	};
}
#endif
