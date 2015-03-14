#include "pebble.h"
#include "main.h" // Used for drawing hands
#ifdef PBL_COLOR // Only use this for color screens
  #include "gcolor_definitions.h" // Allows the use of colors such as "GColorMidnightGreen"
#endif

static Window *s_main_window; // Main window
static Layer *s_solid_bg_layer, *s_hands_layer; // Solid background and hand layers
static BitmapLayer *s_background_layer; // Background bitmap layer
static GBitmap *s_background_bitmap; // The bitmap that goes on the above layer
static GPath *s_minute_arrow, *s_hour_arrow, *s_second_arrow; // Path for hands

// Update background when called
static void bg_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite); // Set the fill color
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone); // Fill the screen
}

// Update hands when called
static void hands_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer); // Set the bounds of the screen
  
  time_t now = time(NULL); // Get the time
  struct tm *t = localtime(&now); // Get the structure of the time
  
  // Hour hand
  #ifdef PBL_COLOR // For color screens
    graphics_context_set_fill_color(ctx, GColorMidnightGreen); // Set fill color
  #else // For black and white screens
    graphics_context_set_fill_color(ctx, GColorWhite); // Set fill color
    graphics_context_set_stroke_color(ctx, GColorBlack); // Set outline color
  #endif
  gpath_rotate_to(s_hour_arrow, (TRIG_MAX_ANGLE * (((t->tm_hour % 12) * 6) + (t->tm_min / 10))) / (12 * 6)); // Define the path that the hour hand will follow
  gpath_draw_filled(ctx, s_hour_arrow); // Fill the hand with the above color
  #ifdef PBL_COLOR
  #else 
    gpath_draw_outline(ctx, s_hour_arrow); // Draw outline if black and white
  #endif

  // Minute hand
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorDarkCandyAppleRed); // Set fill color
  #endif // No need to redefine for black and white screens
  gpath_rotate_to(s_minute_arrow, TRIG_MAX_ANGLE * t->tm_min / 60); // Define the path that the minute hand will follow
  gpath_draw_filled(ctx, s_minute_arrow); // Fill the hand with the above color
  #ifdef PBL_COLOR
  #else 
    gpath_draw_outline(ctx, s_minute_arrow); // Draw outline if black and white
  #endif
  
  //Second hand
  #ifdef PBL_COLOR // For color screens
    graphics_context_set_fill_color(ctx, GColorLimerick); // Set fill color
  #else // For black and white screens.
    graphics_context_set_fill_color(ctx, GColorBlack); // Set fill color
  #endif
  gpath_rotate_to(s_second_arrow, (TRIG_MAX_ANGLE * t->tm_sec / 60)); // Define the path that the minute hand will follow
  gpath_draw_filled(ctx, s_second_arrow); // Fill the hand with the above color

  // Center dot
  #ifdef PBL_COLOR // For color screens
    graphics_context_set_fill_color(ctx, GColorBlack); // Set fill color
  #else // For black and white screens
    graphics_context_set_fill_color(ctx, GColorWhite); // Set fill color
  #endif
  graphics_fill_rect(ctx, GRect(bounds.size.w / 2 - 1, bounds.size.h / 2 - 1, 3, 3), 0, GCornerNone); // Define the position and size of the center dot
}

// Update hands every second when called
static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(window_get_root_layer(s_main_window));
}

// Loads the layers onto the main window
static void window_load(Window *s_main_window) {
  Layer *window_layer = window_get_root_layer(s_main_window); // Creates a main layer for the entire window
  GRect bounds = layer_get_bounds(window_layer); // Sets the bounds of the main layer
  
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND); // Set the background bitmap resource

  s_solid_bg_layer = layer_create(bounds); // Create the simple single color background
  s_background_layer = bitmap_layer_create(bounds); // Create the watch face layer
  s_hands_layer = layer_create(bounds); // Create the hands layer
  
  layer_set_update_proc(s_solid_bg_layer, bg_update_proc); // Call the background update function
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap); // Set the bitmap image to the background layer
  layer_set_update_proc(s_hands_layer, hands_update_proc); // Call the hands update function
  
  #if PBL_PLATFORM_BASALT // Only set this for SDK 3.0 +
    bitmap_layer_set_compositing_mode(s_background_layer, GCompOpSet); // Set background layer to be transparent
  #endif
  
  layer_add_child(window_layer, s_solid_bg_layer); // Add the background layer to the main layer
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer)); // Add the face layer to the main layer
  layer_add_child(window_layer, s_hands_layer); // Add the hands layer to the main layer
}

// Unload the layers from the main window
static void window_unload(Window *s_main_window) {
  layer_destroy(s_solid_bg_layer); // Destroy the background color
  gbitmap_destroy(s_background_bitmap); // Destroy the background bitmap
  bitmap_layer_destroy(s_background_layer); // Destroy the face layer
  layer_destroy(s_hands_layer); // Destroy the hands layer
}

// Initialize the main window
static void init() {
  s_main_window = window_create(); // Create the window on initialization
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load, // Allow the window_load function to handle the window
    .unload = window_unload, // Allow the window_unload function to handle the window
  });
  window_stack_push(s_main_window, true); // Show the window. Animated = true

  s_minute_arrow = gpath_create(&MINUTE_HAND_POINTS); // Initialize the path of the minute hand from the main.h file
  s_hour_arrow = gpath_create(&HOUR_HAND_POINTS); // Initialize the path of the hour hand from the main.h file
  s_second_arrow = gpath_create(&SECOND_HAND_POINTS); // Initialize the path of the second hand from the main.h file

  Layer *window_layer = window_get_root_layer(s_main_window); // Create the root layer of the window
  GRect bounds = layer_get_bounds(window_layer); // Set the bounds of that layer
  GPoint center = grect_center_point(&bounds); // Set the center of the layer
  gpath_move_to(s_minute_arrow, center); // Move the minute hand to the center
  gpath_move_to(s_hour_arrow, center); // Move the hour hand to the center
  gpath_move_to(s_second_arrow, center); // Move the second hand to the center

  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick); // Call to the handle_second_tick to update the watch every second
}

// Deinitialize the main window
static void deinit() {
  
  gpath_destroy(s_minute_arrow); // Destroy the minute hand
  gpath_destroy(s_hour_arrow); // Destroy the hour hand
  gpath_destroy(s_second_arrow); // Destroy the second hand

  tick_timer_service_unsubscribe();   // Unsubscribe from the tick timer
  
  window_destroy(s_main_window);   // Destroy the main window
}

int main() {
  init();
  app_event_loop();
  deinit();
}
