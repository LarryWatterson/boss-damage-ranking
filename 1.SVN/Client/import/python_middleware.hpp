#ifndef PYTHONMIDDLEWARE_HPP
#define PYTHONMIDDLEWARE_HPP

namespace helpers {

class PythonMiddleWare {
  public:
    /**
     * @brief Set Python window
     *
     * @param po_wnd Python window
     */
    void set_ui_window(PyObject* po_wnd)
    {
        m_po_window = po_wnd;
    }

    /**
     * @brief Call Python function
     *
     * @param c_func Function name
     * @param po_args Arguments
     */
    void call_window_func(const char* c_func, PyObject* po_args) const
    {
        if (nullptr == m_po_window) { return; }

        auto* const args{nullptr != po_args ? Py_BuildValue("(O)", po_args) : Py_BuildValue("()")};

        PyCallClassMemberFunc(m_po_window, c_func, args);
    }

  private:
    /**
     * @brief Python window object
     */
    PyObject* m_po_window{};
};

/**
 * @brief PyHelper type alias.
 */
using py_helper_t = std::unique_ptr<PythonMiddleWare>;

} // namespace helpers

#endif
