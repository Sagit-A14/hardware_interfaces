/*
 * Copyright (C) 2020 The Android Open Source Project
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

#include "MessageDefinition.h"

namespace android::nl::protocols {

AttributeMap::AttributeMap(const std::initializer_list<value_type> attrTypes)
    : std::map<std::optional<nlattrtype_t>, AttributeDefinition>(attrTypes) {}

const AttributeDefinition AttributeMap::operator[](nlattrtype_t nla_type) const {
    if (count(nla_type) == 0) {
        if (count(std::nullopt) == 0) return {std::to_string(nla_type)};

        auto definition = find(std::nullopt)->second;
        definition.name += std::to_string(nla_type);
        return definition;
    }
    return find(nla_type)->second;
}

MessageDescriptor::MessageDescriptor(const std::string& name, const MessageTypeMap&& messageTypes,
                                     const AttributeMap&& attrTypes, size_t contentsSize)
    : mName(name),
      mContentsSize(contentsSize),
      mMessageTypes(messageTypes),
      mAttributeMap(attrTypes) {}

MessageDescriptor::~MessageDescriptor() {}

size_t MessageDescriptor::getContentsSize() const {
    return mContentsSize;
}

const MessageDescriptor::MessageTypeMap& MessageDescriptor::getMessageTypeMap() const {
    return mMessageTypes;
}

const AttributeMap& MessageDescriptor::getAttributeMap() const {
    return mAttributeMap;
}

const std::string MessageDescriptor::getMessageName(nlmsgtype_t msgtype) const {
    const auto it = mMessageTypes.find(msgtype);
    if (it == mMessageTypes.end()) return "?";
    return it->second;
}

}  // namespace android::nl::protocols