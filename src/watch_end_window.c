#include <pebble.h>

// Amount of time, in milliseconds, to flash window
#define WATCH_END_FLASH_TIME 750

// Defining a Window object
static Window *s_watch_end_window;

// Bitmap pointer and layer for the png image
static GBitmap *s_watch_end_bitmap;
static BitmapLayer *s_watch_end_bitmap_layer;

// When called, remove the Window from the stack
void timer3_callback(void *data) {
  window_stack_pop(true);
}

// Window load handler
static void watch_end_window_load(Window *window) {
  app_timer_register(WATCH_END_FLASH_TIME, (AppTimerCallback) timer3_callback, NULL);
  Layer *window_layer = window_get_root_layer(s_watch_end_window);
  s_watch_end_bitmap = gbitmap_create_with_resource(RESOURCE_ID_WATCH_END_144PX);
  s_watch_end_bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 144));
  bitmap_layer_set_bitmap(s_watch_end_bitmap_layer, s_watch_end_bitmap);
  layer_add_child(window_get_root_layer(s_watch_end_window), bitmap_layer_get_layer(s_watch_end_bitmap_layer));
}

// Window unload handler
static void watch_end_window_unload(Window *window) {
  gbitmap_destroy(s_watch_end_bitmap);
  bitmap_layer_destroy(s_watch_end_bitmap_layer);
}

// Initialize Window
void init_watch_end_window() {
  // Create main Window element and assign to pointer
  s_watch_end_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_watch_end_window, (WindowHandlers) {
    .load = watch_end_window_load,
    .unload = watch_end_window_unload,
  });
  
  // Show the Window on the watch
  window_stack_push(s_watch_end_window, true);
}

// Destroy Window
void deinit_watch_end_window() {
  window_destroy(s_watch_end_window);
}