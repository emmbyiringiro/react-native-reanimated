//
// Created by Szymon Kapala on 2020-02-11.
//

#include "SharedValueRegistry.h"
#include "Logger.h"

void SharedValueRegistry::registerSharedValue(int id, std::shared_ptr<SharedValue> ptr) {
  sharedValueMap[id] = ptr;
}

void SharedValueRegistry::unregisterSharedValue(int id, jsi::Runtime &rt) {
  if (sharedValueMap.find(id) != sharedValueMap.end()) {
    sharedValueMap[id]->willUnregister(rt);
  }
  sharedValueMap.erase(id);
}

std::shared_ptr<SharedValue> SharedValueRegistry::getSharedValue(int id) {
  auto it = sharedValueMap.find(id);
  if (it == sharedValueMap.end()) {
    return nullptr;
  }
  return it->second;
}


std::unordered_map<int, std::shared_ptr<SharedValue>> SharedValueRegistry::getSharedValueMap() const {
  return this->sharedValueMap;
}

int SharedValueRegistry::NEXT_SHARED_VALUE_ID = INT_MAX;
