// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: skill.proto

#ifndef PROTOBUF_skill_2eproto__INCLUDED
#define PROTOBUF_skill_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace amarlon {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_skill_2eproto();
void protobuf_AssignDesc_skill_2eproto();
void protobuf_ShutdownFile_skill_2eproto();

class SkillData;
class SkillsData;

// ===================================================================

class SkillData : public ::google::protobuf::Message {
 public:
  SkillData();
  virtual ~SkillData();

  SkillData(const SkillData& from);

  inline SkillData& operator=(const SkillData& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SkillData& default_instance();

  void Swap(SkillData* other);

  // implements Message ----------------------------------------------

  SkillData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SkillData& from);
  void MergeFrom(const SkillData& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // optional int32 level = 2 [default = 0];
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 2;
  inline ::google::protobuf::int32 level() const;
  inline void set_level(::google::protobuf::int32 value);

  // optional bool passive = 3 [default = false];
  inline bool has_passive() const;
  inline void clear_passive();
  static const int kPassiveFieldNumber = 3;
  inline bool passive() const;
  inline void set_passive(bool value);

  // optional int32 range = 4 [default = 0];
  inline bool has_range() const;
  inline void clear_range();
  static const int kRangeFieldNumber = 4;
  inline ::google::protobuf::int32 range() const;
  inline void set_range(::google::protobuf::int32 value);

  // optional int32 radius = 5 [default = 0];
  inline bool has_radius() const;
  inline void clear_radius();
  static const int kRadiusFieldNumber = 5;
  inline ::google::protobuf::int32 radius() const;
  inline void set_radius(::google::protobuf::int32 value);

  // optional int32 target_type = 6 [default = 0];
  inline bool has_target_type() const;
  inline void clear_target_type();
  static const int kTargetTypeFieldNumber = 6;
  inline ::google::protobuf::int32 target_type() const;
  inline void set_target_type(::google::protobuf::int32 value);

  // required string name = 7;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 7;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional string description = 8 [default = ""];
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 8;
  inline const ::std::string& description() const;
  inline void set_description(const ::std::string& value);
  inline void set_description(const char* value);
  inline void set_description(const char* value, size_t size);
  inline ::std::string* mutable_description();
  inline ::std::string* release_description();
  inline void set_allocated_description(::std::string* description);

  // @@protoc_insertion_point(class_scope:amarlon.SkillData)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_passive();
  inline void clear_has_passive();
  inline void set_has_range();
  inline void clear_has_range();
  inline void set_has_radius();
  inline void clear_has_radius();
  inline void set_has_target_type();
  inline void clear_has_target_type();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_description();
  inline void clear_has_description();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 level_;
  bool passive_;
  ::google::protobuf::int32 range_;
  ::google::protobuf::int32 radius_;
  ::google::protobuf::int32 target_type_;
  ::std::string* name_;
  ::std::string* description_;
  friend void  protobuf_AddDesc_skill_2eproto();
  friend void protobuf_AssignDesc_skill_2eproto();
  friend void protobuf_ShutdownFile_skill_2eproto();

  void InitAsDefaultInstance();
  static SkillData* default_instance_;
};
// -------------------------------------------------------------------

class SkillsData : public ::google::protobuf::Message {
 public:
  SkillsData();
  virtual ~SkillsData();

  SkillsData(const SkillsData& from);

  inline SkillsData& operator=(const SkillsData& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SkillsData& default_instance();

  void Swap(SkillsData* other);

  // implements Message ----------------------------------------------

  SkillsData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SkillsData& from);
  void MergeFrom(const SkillsData& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .amarlon.SkillData skill = 1;
  inline int skill_size() const;
  inline void clear_skill();
  static const int kSkillFieldNumber = 1;
  inline const ::amarlon::SkillData& skill(int index) const;
  inline ::amarlon::SkillData* mutable_skill(int index);
  inline ::amarlon::SkillData* add_skill();
  inline const ::google::protobuf::RepeatedPtrField< ::amarlon::SkillData >&
      skill() const;
  inline ::google::protobuf::RepeatedPtrField< ::amarlon::SkillData >*
      mutable_skill();

  // @@protoc_insertion_point(class_scope:amarlon.SkillsData)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::amarlon::SkillData > skill_;
  friend void  protobuf_AddDesc_skill_2eproto();
  friend void protobuf_AssignDesc_skill_2eproto();
  friend void protobuf_ShutdownFile_skill_2eproto();

  void InitAsDefaultInstance();
  static SkillsData* default_instance_;
};
// ===================================================================


// ===================================================================

// SkillData

// required int32 id = 1;
inline bool SkillData::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SkillData::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SkillData::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SkillData::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 SkillData::id() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.id)
  return id_;
}
inline void SkillData::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SkillData.id)
}

// optional int32 level = 2 [default = 0];
inline bool SkillData::has_level() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SkillData::set_has_level() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SkillData::clear_has_level() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SkillData::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 SkillData::level() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.level)
  return level_;
}
inline void SkillData::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SkillData.level)
}

// optional bool passive = 3 [default = false];
inline bool SkillData::has_passive() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SkillData::set_has_passive() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SkillData::clear_has_passive() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SkillData::clear_passive() {
  passive_ = false;
  clear_has_passive();
}
inline bool SkillData::passive() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.passive)
  return passive_;
}
inline void SkillData::set_passive(bool value) {
  set_has_passive();
  passive_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SkillData.passive)
}

// optional int32 range = 4 [default = 0];
inline bool SkillData::has_range() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SkillData::set_has_range() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SkillData::clear_has_range() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SkillData::clear_range() {
  range_ = 0;
  clear_has_range();
}
inline ::google::protobuf::int32 SkillData::range() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.range)
  return range_;
}
inline void SkillData::set_range(::google::protobuf::int32 value) {
  set_has_range();
  range_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SkillData.range)
}

// optional int32 radius = 5 [default = 0];
inline bool SkillData::has_radius() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SkillData::set_has_radius() {
  _has_bits_[0] |= 0x00000010u;
}
inline void SkillData::clear_has_radius() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void SkillData::clear_radius() {
  radius_ = 0;
  clear_has_radius();
}
inline ::google::protobuf::int32 SkillData::radius() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.radius)
  return radius_;
}
inline void SkillData::set_radius(::google::protobuf::int32 value) {
  set_has_radius();
  radius_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SkillData.radius)
}

// optional int32 target_type = 6 [default = 0];
inline bool SkillData::has_target_type() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void SkillData::set_has_target_type() {
  _has_bits_[0] |= 0x00000020u;
}
inline void SkillData::clear_has_target_type() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void SkillData::clear_target_type() {
  target_type_ = 0;
  clear_has_target_type();
}
inline ::google::protobuf::int32 SkillData::target_type() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.target_type)
  return target_type_;
}
inline void SkillData::set_target_type(::google::protobuf::int32 value) {
  set_has_target_type();
  target_type_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SkillData.target_type)
}

// required string name = 7;
inline bool SkillData::has_name() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void SkillData::set_has_name() {
  _has_bits_[0] |= 0x00000040u;
}
inline void SkillData::clear_has_name() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void SkillData::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& SkillData::name() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.name)
  return *name_;
}
inline void SkillData::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:amarlon.SkillData.name)
}
inline void SkillData::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:amarlon.SkillData.name)
}
inline void SkillData::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:amarlon.SkillData.name)
}
inline ::std::string* SkillData::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:amarlon.SkillData.name)
  return name_;
}
inline ::std::string* SkillData::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SkillData::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:amarlon.SkillData.name)
}

// optional string description = 8 [default = ""];
inline bool SkillData::has_description() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void SkillData::set_has_description() {
  _has_bits_[0] |= 0x00000080u;
}
inline void SkillData::clear_has_description() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void SkillData::clear_description() {
  if (description_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_->clear();
  }
  clear_has_description();
}
inline const ::std::string& SkillData::description() const {
  // @@protoc_insertion_point(field_get:amarlon.SkillData.description)
  return *description_;
}
inline void SkillData::set_description(const ::std::string& value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  description_->assign(value);
  // @@protoc_insertion_point(field_set:amarlon.SkillData.description)
}
inline void SkillData::set_description(const char* value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  description_->assign(value);
  // @@protoc_insertion_point(field_set_char:amarlon.SkillData.description)
}
inline void SkillData::set_description(const char* value, size_t size) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  description_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:amarlon.SkillData.description)
}
inline ::std::string* SkillData::mutable_description() {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:amarlon.SkillData.description)
  return description_;
}
inline ::std::string* SkillData::release_description() {
  clear_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = description_;
    description_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SkillData::set_allocated_description(::std::string* description) {
  if (description_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete description_;
  }
  if (description) {
    set_has_description();
    description_ = description;
  } else {
    clear_has_description();
    description_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:amarlon.SkillData.description)
}

// -------------------------------------------------------------------

// SkillsData

// repeated .amarlon.SkillData skill = 1;
inline int SkillsData::skill_size() const {
  return skill_.size();
}
inline void SkillsData::clear_skill() {
  skill_.Clear();
}
inline const ::amarlon::SkillData& SkillsData::skill(int index) const {
  // @@protoc_insertion_point(field_get:amarlon.SkillsData.skill)
  return skill_.Get(index);
}
inline ::amarlon::SkillData* SkillsData::mutable_skill(int index) {
  // @@protoc_insertion_point(field_mutable:amarlon.SkillsData.skill)
  return skill_.Mutable(index);
}
inline ::amarlon::SkillData* SkillsData::add_skill() {
  // @@protoc_insertion_point(field_add:amarlon.SkillsData.skill)
  return skill_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::amarlon::SkillData >&
SkillsData::skill() const {
  // @@protoc_insertion_point(field_list:amarlon.SkillsData.skill)
  return skill_;
}
inline ::google::protobuf::RepeatedPtrField< ::amarlon::SkillData >*
SkillsData::mutable_skill() {
  // @@protoc_insertion_point(field_mutable_list:amarlon.SkillsData.skill)
  return &skill_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace amarlon

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_skill_2eproto__INCLUDED