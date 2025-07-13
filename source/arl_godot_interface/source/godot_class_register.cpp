#include <godot_cpp/godot.hpp>
#include <arl_godot_interface/godot_import_wrapper.hpp>

using namespace godot;
using namespace arl_godot_interface;

void initialize_godot_import_wrapper_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    GDREGISTER_RUNTIME_CLASS(GodotImportWrapper);
}

void uninitialize_godot_import_wrapper_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT godot_import_wrapper_init(GDExtensionInterfaceGetProcAddress p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization) {
        static GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);
        init_obj.register_initializer(initialize_godot_import_wrapper_module);
        init_obj.register_terminator(uninitialize_godot_import_wrapper_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}