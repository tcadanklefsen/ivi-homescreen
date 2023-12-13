/*
 * Copyright 2020-2023 Toyota Connected North America
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "projection.h"

namespace view_filament_view {

Projection::Projection(void const* parent,
                       const std::string& flutter_assets_path,
                       const flutter::EncodableMap& params)
    : parent_(parent), flutterAssetsPath_(flutter_assets_path) {
  for (auto& it : params) {
    if (it.second.IsNull())
      continue;

    auto key = std::get<std::string>(it.first);
    if (key == "projection" && std::holds_alternative<std::string>(it.second)) {
      projection_ = getTypeForText(std::get<std::string>(it.second));
    } else if (key == "left" && std::holds_alternative<double>(it.second)) {
      left_ = std::get<double>(it.second);
    } else if (key == "right" && std::holds_alternative<double>(it.second)) {
      right_ = std::get<double>(it.second);
    } else if (key == "bottom" && std::holds_alternative<double>(it.second)) {
      bottom_ = std::get<double>(it.second);
    } else if (key == "top" && std::holds_alternative<double>(it.second)) {
      top_ = std::get<double>(it.second);
    } else if (key == "near" && std::holds_alternative<double>(it.second)) {
      near_ = std::get<double>(it.second);
    } else if (key == "far" && std::holds_alternative<double>(it.second)) {
      far_ = std::get<double>(it.second);
    } else if (key == "fovInDegrees" &&
               std::holds_alternative<double>(it.second)) {
      fovInDegrees_ = std::get<double>(it.second);
    } else if (key == "aspect" && std::holds_alternative<double>(it.second)) {
      aspect_ = std::get<double>(it.second);
    } else if (key == "direction" && !it.second.IsNull() &&
               std::holds_alternative<std::string>(it.second)) {
      fovDirection_ = getFovForText(std::get<std::string>(it.second));
    } else if (!it.second.IsNull()) {
      spdlog::debug("[Projection] Unhandled Parameter");
      Utils::PrintFlutterEncodableValue(key.c_str(), it.second);
    }
  }
}

void Projection::Print(const char* tag) {
  spdlog::debug("++++++++");
  spdlog::debug("{} (Projection)", tag);
  if (projection_.has_value()) {
    spdlog::debug("projection: {}", getTextForType(projection_.value()));
  }
  if (left_.has_value()) {
    spdlog::debug("left: {}", left_.value());
  }
  if (right_.has_value()) {
    spdlog::debug("right: {}", right_.value());
  }
  if (bottom_.has_value()) {
    spdlog::debug("bottom: {}", bottom_.value());
  }
  if (top_.has_value()) {
    spdlog::debug("top: {}", top_.value());
  }
  if (near_.has_value()) {
    spdlog::debug("near: {}", near_.value());
  }
  if (far_.has_value()) {
    spdlog::debug("far: {}", far_.value());
  }
  if (fovInDegrees_.has_value()) {
    spdlog::debug("fovInDegrees: {}", fovInDegrees_.value());
  }
  if (aspect_.has_value()) {
    spdlog::debug("aspect: {}", aspect_.value());
  }
  if (fovDirection_.has_value()) {
    spdlog::debug("fovDirection: {}", getTextForFov(fovDirection_.value()));
  }
  spdlog::debug("++++++++");
}

const char* Projection::getTextForType(Projection::Type type) {
  return (const char*[]){
      kTypePerspective,
      kTypeOrtho,
  }[static_cast<int>(type)];
}

Projection::Type Projection::getTypeForText(const std::string& type) {
  if (type == kTypePerspective)
    return Type::perspective;
  return Type::ortho;
}

const char* Projection::getTextForFov(Projection::Fov fov) {
  return (const char*[]){
      kFovVertical,
      kFovHorizontal,
  }[static_cast<int>(fov)];
}

Projection::Fov Projection::getFovForText(const std::string& fov) {
  if (fov == kFovVertical) {
    return Fov::vertical;
  } else if (fov == kFovHorizontal) {
    return Fov::horizontal;
  }
  return Fov::horizontal;
}

}  // namespace view_filament_view
