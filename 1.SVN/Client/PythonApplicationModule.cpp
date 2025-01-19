// find

	PyModule_AddIntConstant(poModule, "CAMERA_STOP",			CPythonApplication::CAMERA_STOP);

// add below

#ifdef BOSS_DAMAGE_RANKING_PLUGIN
        PyModule_AddIntConstant(poModule, "BOSS_DAMAGE_RANKING_PLUGIN", true);
#else
        PyModule_AddIntConstant(poModule, "BOSS_DAMAGE_RANKING_PLUGIN", false);
#endif
