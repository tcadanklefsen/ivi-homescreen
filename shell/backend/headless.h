
#pragma once

#include <cstdint>

#include "backend.h"
#include "constants.h"

#include <GL/osmesa.h>

class HeadlessBackend : public Backend {
 public:
  HeadlessBackend(uint32_t initial_width, uint32_t initial_height);

  /**
   * @brief Resize Flutter engine Window size
   * @param[in] user_data Pointer to User data
   * @param[in] index No use
   * @param[in] engine Pointer to Flutter engine
   * @param[in] width Set window width
   * @param[in] height Set window height
   * @return void
   * @relation
   * wayland
   */
  static void Resize(void* user_data,
              size_t index,
              Engine* engine,
              int32_t width,
              int32_t height);

  /**
   * @brief Create EGL surface
   * @param[in] user_data Pointer to User data
   * @param[in] index No use
   * @param[in] surface Pointer to surface
   * @param[in] width Set surface width
   * @param[in] height Set surface height
   * @return void
   * @relation
   * wayland
   */
  static void CreateSurface(void* user_data,
                            size_t index,
                            wl_surface* surface,
                            int32_t width,
                            int32_t height);

  /**
   * @brief Get FlutterRendererConfig
   * @return FlutterRendererConfig
   * @retval Pointer to FlutterRendererConfig
   * @relation
   * wayland
   */
  FlutterRendererConfig GetRenderConfig() override;

  /**
   * @brief Get FlutterCompositor
   * @return FlutterCompositor
   * @retval Pointer to FlutterCompositor
   * @relation
   * wayland
   */
  FlutterCompositor GetCompositorConfig() override;

 private:
  uint32_t m_prev_width, m_width;
  uint32_t m_prev_height, m_height;
};
