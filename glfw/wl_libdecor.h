/*
 * wl_libdecor.h - libdecor integration for GLFW (dlopen-based)
 * Copyright (C) 2026 kitty contributors
 *
 * Distributed under terms of the GPL3 license.
 */

#pragma once

#include <stdbool.h>
#include <wayland-client.h>

// Opaque types from libdecor
struct libdecor;
struct libdecor_frame;
struct libdecor_configuration;
struct libdecor_state;

enum libdecor_error {
    LIBDECOR_ERROR_COMPOSITOR_INCOMPATIBLE,
    LIBDECOR_ERROR_INVALID_FRAME_CONFIGURATION,
};

enum libdecor_window_state {
    LIBDECOR_WINDOW_STATE_NONE = 0,
    LIBDECOR_WINDOW_STATE_ACTIVE = 1 << 0,
    LIBDECOR_WINDOW_STATE_MAXIMIZED = 1 << 1,
    LIBDECOR_WINDOW_STATE_FULLSCREEN = 1 << 2,
    LIBDECOR_WINDOW_STATE_TILED_LEFT = 1 << 3,
    LIBDECOR_WINDOW_STATE_TILED_RIGHT = 1 << 4,
    LIBDECOR_WINDOW_STATE_TILED_TOP = 1 << 5,
    LIBDECOR_WINDOW_STATE_TILED_BOTTOM = 1 << 6,
};

enum libdecor_capabilities {
    LIBDECOR_ACTION_MOVE = 1 << 0,
    LIBDECOR_ACTION_RESIZE = 1 << 1,
    LIBDECOR_ACTION_MINIMIZE = 1 << 2,
    LIBDECOR_ACTION_FULLSCREEN = 1 << 3,
    LIBDECOR_ACTION_CLOSE = 1 << 4,
};

struct libdecor_interface {
    void (*error)(struct libdecor *context,
                  enum libdecor_error error,
                  const char *message);
    void (*reserved0)(void);
    void (*reserved1)(void);
    void (*reserved2)(void);
    void (*reserved3)(void);
    void (*reserved4)(void);
    void (*reserved5)(void);
    void (*reserved6)(void);
    void (*reserved7)(void);
    void (*reserved8)(void);
    void (*reserved9)(void);
};

struct libdecor_frame_interface {
    void (*configure)(struct libdecor_frame *frame,
                      struct libdecor_configuration *configuration,
                      void *user_data);
    void (*close)(struct libdecor_frame *frame,
                  void *user_data);
    void (*commit)(struct libdecor_frame *frame,
                   void *user_data);
    void (*dismiss_popup)(struct libdecor_frame *frame,
                          const char *seat_name,
                          void *user_data);
    void (*reserved0)(void);
    void (*reserved1)(void);
    void (*reserved2)(void);
    void (*reserved3)(void);
    void (*reserved4)(void);
    void (*reserved5)(void);
    void (*reserved6)(void);
    void (*reserved7)(void);
    void (*reserved8)(void);
    void (*reserved9)(void);
};

// Function pointer typedefs for dlopen
typedef struct libdecor* (*PFN_libdecor_new)(struct wl_display*, struct libdecor_interface*);
typedef void (*PFN_libdecor_unref)(struct libdecor*);
typedef int (*PFN_libdecor_get_fd)(struct libdecor*);
typedef int (*PFN_libdecor_dispatch)(struct libdecor*, int timeout);

typedef struct libdecor_frame* (*PFN_libdecor_decorate)(struct libdecor*, struct wl_surface*, struct libdecor_frame_interface*, void*);
typedef void (*PFN_libdecor_frame_unref)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_set_app_id)(struct libdecor_frame*, const char*);
typedef void (*PFN_libdecor_frame_set_title)(struct libdecor_frame*, const char*);
typedef void (*PFN_libdecor_frame_set_minimized)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_set_maximized)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_unset_maximized)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_set_fullscreen)(struct libdecor_frame*, struct wl_output*);
typedef void (*PFN_libdecor_frame_unset_fullscreen)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_set_capabilities)(struct libdecor_frame*, enum libdecor_capabilities);
typedef void (*PFN_libdecor_frame_unset_capabilities)(struct libdecor_frame*, enum libdecor_capabilities);
typedef void (*PFN_libdecor_frame_set_visibility)(struct libdecor_frame*, bool visible);
typedef bool (*PFN_libdecor_frame_is_visible)(struct libdecor_frame*);
typedef bool (*PFN_libdecor_frame_is_floating)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_set_max_content_size)(struct libdecor_frame*, int, int);
typedef void (*PFN_libdecor_frame_set_min_content_size)(struct libdecor_frame*, int, int);
typedef void (*PFN_libdecor_frame_resize)(struct libdecor_frame*, struct wl_seat*, uint32_t, int);
typedef void (*PFN_libdecor_frame_move)(struct libdecor_frame*, struct wl_seat*, uint32_t);
typedef void (*PFN_libdecor_frame_commit)(struct libdecor_frame*, struct libdecor_state*, struct libdecor_configuration*);
typedef void (*PFN_libdecor_frame_set_parent)(struct libdecor_frame*, struct libdecor_frame*);
typedef struct xdg_surface* (*PFN_libdecor_frame_get_xdg_surface)(struct libdecor_frame*);
typedef struct xdg_toplevel* (*PFN_libdecor_frame_get_xdg_toplevel)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_map)(struct libdecor_frame*);
typedef void (*PFN_libdecor_frame_translate_coordinate)(struct libdecor_frame*, int, int, int*, int*);

typedef struct libdecor_state* (*PFN_libdecor_state_new)(int, int);
typedef void (*PFN_libdecor_state_free)(struct libdecor_state*);

typedef bool (*PFN_libdecor_configuration_get_content_size)(struct libdecor_configuration*, struct libdecor_frame*, int*, int*);
typedef bool (*PFN_libdecor_configuration_get_window_state)(struct libdecor_configuration*, enum libdecor_window_state*);
