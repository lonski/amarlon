// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: spell.proto

#ifndef PROTOBUF_spell_2eproto__INCLUDED
#define PROTOBUF_spell_2eproto__INCLUDED

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
void  protobuf_AddDesc_spell_2eproto();
void protobuf_AssignDesc_spell_2eproto();
void protobuf_ShutdownFile_spell_2eproto();

class SpellData;
class SpellsData;
class SpellBookData;
class SpellBookData_SlotData;

// ===================================================================

class SpellData : public ::google::protobuf::Message {
 public:
  SpellData();
  virtual ~SpellData();

  SpellData(const SpellData& from);

  inline SpellData& operator=(const SpellData& from) {
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
  static const SpellData& default_instance();

  void Swap(SpellData* other);

  // implements Message ----------------------------------------------

  SpellData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SpellData& from);
  void MergeFrom(const SpellData& from);
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

  // required int32 level = 2;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 2;
  inline ::google::protobuf::int32 level() const;
  inline void set_level(::google::protobuf::int32 value);

  // required int32 char_class = 3;
  inline bool has_char_class() const;
  inline void clear_char_class();
  static const int kCharClassFieldNumber = 3;
  inline ::google::protobuf::int32 char_class() const;
  inline void set_char_class(::google::protobuf::int32 value);

  // optional int32 target_type = 4 [default = 0];
  inline bool has_target_type() const;
  inline void clear_target_type();
  static const int kTargetTypeFieldNumber = 4;
  inline ::google::protobuf::int32 target_type() const;
  inline void set_target_type(::google::protobuf::int32 value);

  // required string name = 5;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 5;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required string description = 6;
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 6;
  inline const ::std::string& description() const;
  inline void set_description(const ::std::string& value);
  inline void set_description(const char* value);
  inline void set_description(const char* value, size_t size);
  inline ::std::string* mutable_description();
  inline ::std::string* release_description();
  inline void set_allocated_description(::std::string* description);

  // optional bool passive = 7 [default = false];
  inline bool has_passive() const;
  inline void clear_passive();
  static const int kPassiveFieldNumber = 7;
  inline bool passive() const;
  inline void set_passive(bool value);

  // optional int32 radius = 8 [default = 0];
  inline bool has_radius() const;
  inline void clear_radius();
  static const int kRadiusFieldNumber = 8;
  inline ::google::protobuf::int32 radius() const;
  inline void set_radius(::google::protobuf::int32 value);

  // optional int32 range = 9 [default = 0];
  inline bool has_range() const;
  inline void clear_range();
  static const int kRangeFieldNumber = 9;
  inline ::google::protobuf::int32 range() const;
  inline void set_range(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:amarlon.SpellData)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_char_class();
  inline void clear_has_char_class();
  inline void set_has_target_type();
  inline void clear_has_target_type();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_description();
  inline void clear_has_description();
  inline void set_has_passive();
  inline void clear_has_passive();
  inline void set_has_radius();
  inline void clear_has_radius();
  inline void set_has_range();
  inline void clear_has_range();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 level_;
  ::google::protobuf::int32 char_class_;
  ::google::protobuf::int32 target_type_;
  ::std::string* name_;
  ::std::string* description_;
  bool passive_;
  ::google::protobuf::int32 radius_;
  ::google::protobuf::int32 range_;
  friend void  protobuf_AddDesc_spell_2eproto();
  friend void protobuf_AssignDesc_spell_2eproto();
  friend void protobuf_ShutdownFile_spell_2eproto();

  void InitAsDefaultInstance();
  static SpellData* default_instance_;
};
// -------------------------------------------------------------------

class SpellsData : public ::google::protobuf::Message {
 public:
  SpellsData();
  virtual ~SpellsData();

  SpellsData(const SpellsData& from);

  inline SpellsData& operator=(const SpellsData& from) {
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
  static const SpellsData& default_instance();

  void Swap(SpellsData* other);

  // implements Message ----------------------------------------------

  SpellsData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SpellsData& from);
  void MergeFrom(const SpellsData& from);
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

  // repeated .amarlon.SpellData spell = 1;
  inline int spell_size() const;
  inline void clear_spell();
  static const int kSpellFieldNumber = 1;
  inline const ::amarlon::SpellData& spell(int index) const;
  inline ::amarlon::SpellData* mutable_spell(int index);
  inline ::amarlon::SpellData* add_spell();
  inline const ::google::protobuf::RepeatedPtrField< ::amarlon::SpellData >&
      spell() const;
  inline ::google::protobuf::RepeatedPtrField< ::amarlon::SpellData >*
      mutable_spell();

  // @@protoc_insertion_point(class_scope:amarlon.SpellsData)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::amarlon::SpellData > spell_;
  friend void  protobuf_AddDesc_spell_2eproto();
  friend void protobuf_AssignDesc_spell_2eproto();
  friend void protobuf_ShutdownFile_spell_2eproto();

  void InitAsDefaultInstance();
  static SpellsData* default_instance_;
};
// -------------------------------------------------------------------

class SpellBookData_SlotData : public ::google::protobuf::Message {
 public:
  SpellBookData_SlotData();
  virtual ~SpellBookData_SlotData();

  SpellBookData_SlotData(const SpellBookData_SlotData& from);

  inline SpellBookData_SlotData& operator=(const SpellBookData_SlotData& from) {
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
  static const SpellBookData_SlotData& default_instance();

  void Swap(SpellBookData_SlotData* other);

  // implements Message ----------------------------------------------

  SpellBookData_SlotData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SpellBookData_SlotData& from);
  void MergeFrom(const SpellBookData_SlotData& from);
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

  // required int32 level = 1;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 1;
  inline ::google::protobuf::int32 level() const;
  inline void set_level(::google::protobuf::int32 value);

  // optional bool isPrepared = 2 [default = false];
  inline bool has_isprepared() const;
  inline void clear_isprepared();
  static const int kIsPreparedFieldNumber = 2;
  inline bool isprepared() const;
  inline void set_isprepared(bool value);

  // required int32 spell_id = 3;
  inline bool has_spell_id() const;
  inline void clear_spell_id();
  static const int kSpellIdFieldNumber = 3;
  inline ::google::protobuf::int32 spell_id() const;
  inline void set_spell_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:amarlon.SpellBookData.SlotData)
 private:
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_isprepared();
  inline void clear_has_isprepared();
  inline void set_has_spell_id();
  inline void clear_has_spell_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 level_;
  bool isprepared_;
  ::google::protobuf::int32 spell_id_;
  friend void  protobuf_AddDesc_spell_2eproto();
  friend void protobuf_AssignDesc_spell_2eproto();
  friend void protobuf_ShutdownFile_spell_2eproto();

  void InitAsDefaultInstance();
  static SpellBookData_SlotData* default_instance_;
};
// -------------------------------------------------------------------

class SpellBookData : public ::google::protobuf::Message {
 public:
  SpellBookData();
  virtual ~SpellBookData();

  SpellBookData(const SpellBookData& from);

  inline SpellBookData& operator=(const SpellBookData& from) {
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
  static const SpellBookData& default_instance();

  void Swap(SpellBookData* other);

  // implements Message ----------------------------------------------

  SpellBookData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SpellBookData& from);
  void MergeFrom(const SpellBookData& from);
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

  typedef SpellBookData_SlotData SlotData;

  // accessors -------------------------------------------------------

  // repeated int32 knownSpells = 1;
  inline int knownspells_size() const;
  inline void clear_knownspells();
  static const int kKnownSpellsFieldNumber = 1;
  inline ::google::protobuf::int32 knownspells(int index) const;
  inline void set_knownspells(int index, ::google::protobuf::int32 value);
  inline void add_knownspells(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      knownspells() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_knownspells();

  // repeated .amarlon.SpellBookData.SlotData spellSlots = 2;
  inline int spellslots_size() const;
  inline void clear_spellslots();
  static const int kSpellSlotsFieldNumber = 2;
  inline const ::amarlon::SpellBookData_SlotData& spellslots(int index) const;
  inline ::amarlon::SpellBookData_SlotData* mutable_spellslots(int index);
  inline ::amarlon::SpellBookData_SlotData* add_spellslots();
  inline const ::google::protobuf::RepeatedPtrField< ::amarlon::SpellBookData_SlotData >&
      spellslots() const;
  inline ::google::protobuf::RepeatedPtrField< ::amarlon::SpellBookData_SlotData >*
      mutable_spellslots();

  // @@protoc_insertion_point(class_scope:amarlon.SpellBookData)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > knownspells_;
  ::google::protobuf::RepeatedPtrField< ::amarlon::SpellBookData_SlotData > spellslots_;
  friend void  protobuf_AddDesc_spell_2eproto();
  friend void protobuf_AssignDesc_spell_2eproto();
  friend void protobuf_ShutdownFile_spell_2eproto();

  void InitAsDefaultInstance();
  static SpellBookData* default_instance_;
};
// ===================================================================


// ===================================================================

// SpellData

// required int32 id = 1;
inline bool SpellData::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SpellData::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SpellData::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SpellData::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 SpellData::id() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.id)
  return id_;
}
inline void SpellData::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellData.id)
}

// required int32 level = 2;
inline bool SpellData::has_level() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SpellData::set_has_level() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SpellData::clear_has_level() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SpellData::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 SpellData::level() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.level)
  return level_;
}
inline void SpellData::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellData.level)
}

// required int32 char_class = 3;
inline bool SpellData::has_char_class() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SpellData::set_has_char_class() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SpellData::clear_has_char_class() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SpellData::clear_char_class() {
  char_class_ = 0;
  clear_has_char_class();
}
inline ::google::protobuf::int32 SpellData::char_class() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.char_class)
  return char_class_;
}
inline void SpellData::set_char_class(::google::protobuf::int32 value) {
  set_has_char_class();
  char_class_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellData.char_class)
}

// optional int32 target_type = 4 [default = 0];
inline bool SpellData::has_target_type() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SpellData::set_has_target_type() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SpellData::clear_has_target_type() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SpellData::clear_target_type() {
  target_type_ = 0;
  clear_has_target_type();
}
inline ::google::protobuf::int32 SpellData::target_type() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.target_type)
  return target_type_;
}
inline void SpellData::set_target_type(::google::protobuf::int32 value) {
  set_has_target_type();
  target_type_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellData.target_type)
}

// required string name = 5;
inline bool SpellData::has_name() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SpellData::set_has_name() {
  _has_bits_[0] |= 0x00000010u;
}
inline void SpellData::clear_has_name() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void SpellData::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& SpellData::name() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.name)
  return *name_;
}
inline void SpellData::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:amarlon.SpellData.name)
}
inline void SpellData::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:amarlon.SpellData.name)
}
inline void SpellData::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:amarlon.SpellData.name)
}
inline ::std::string* SpellData::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:amarlon.SpellData.name)
  return name_;
}
inline ::std::string* SpellData::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SpellData::set_allocated_name(::std::string* name) {
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
  // @@protoc_insertion_point(field_set_allocated:amarlon.SpellData.name)
}

// required string description = 6;
inline bool SpellData::has_description() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void SpellData::set_has_description() {
  _has_bits_[0] |= 0x00000020u;
}
inline void SpellData::clear_has_description() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void SpellData::clear_description() {
  if (description_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_->clear();
  }
  clear_has_description();
}
inline const ::std::string& SpellData::description() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.description)
  return *description_;
}
inline void SpellData::set_description(const ::std::string& value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  description_->assign(value);
  // @@protoc_insertion_point(field_set:amarlon.SpellData.description)
}
inline void SpellData::set_description(const char* value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  description_->assign(value);
  // @@protoc_insertion_point(field_set_char:amarlon.SpellData.description)
}
inline void SpellData::set_description(const char* value, size_t size) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  description_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:amarlon.SpellData.description)
}
inline ::std::string* SpellData::mutable_description() {
  set_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    description_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:amarlon.SpellData.description)
  return description_;
}
inline ::std::string* SpellData::release_description() {
  clear_has_description();
  if (description_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = description_;
    description_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SpellData::set_allocated_description(::std::string* description) {
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
  // @@protoc_insertion_point(field_set_allocated:amarlon.SpellData.description)
}

// optional bool passive = 7 [default = false];
inline bool SpellData::has_passive() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void SpellData::set_has_passive() {
  _has_bits_[0] |= 0x00000040u;
}
inline void SpellData::clear_has_passive() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void SpellData::clear_passive() {
  passive_ = false;
  clear_has_passive();
}
inline bool SpellData::passive() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.passive)
  return passive_;
}
inline void SpellData::set_passive(bool value) {
  set_has_passive();
  passive_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellData.passive)
}

// optional int32 radius = 8 [default = 0];
inline bool SpellData::has_radius() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void SpellData::set_has_radius() {
  _has_bits_[0] |= 0x00000080u;
}
inline void SpellData::clear_has_radius() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void SpellData::clear_radius() {
  radius_ = 0;
  clear_has_radius();
}
inline ::google::protobuf::int32 SpellData::radius() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.radius)
  return radius_;
}
inline void SpellData::set_radius(::google::protobuf::int32 value) {
  set_has_radius();
  radius_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellData.radius)
}

// optional int32 range = 9 [default = 0];
inline bool SpellData::has_range() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void SpellData::set_has_range() {
  _has_bits_[0] |= 0x00000100u;
}
inline void SpellData::clear_has_range() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void SpellData::clear_range() {
  range_ = 0;
  clear_has_range();
}
inline ::google::protobuf::int32 SpellData::range() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellData.range)
  return range_;
}
inline void SpellData::set_range(::google::protobuf::int32 value) {
  set_has_range();
  range_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellData.range)
}

// -------------------------------------------------------------------

// SpellsData

// repeated .amarlon.SpellData spell = 1;
inline int SpellsData::spell_size() const {
  return spell_.size();
}
inline void SpellsData::clear_spell() {
  spell_.Clear();
}
inline const ::amarlon::SpellData& SpellsData::spell(int index) const {
  // @@protoc_insertion_point(field_get:amarlon.SpellsData.spell)
  return spell_.Get(index);
}
inline ::amarlon::SpellData* SpellsData::mutable_spell(int index) {
  // @@protoc_insertion_point(field_mutable:amarlon.SpellsData.spell)
  return spell_.Mutable(index);
}
inline ::amarlon::SpellData* SpellsData::add_spell() {
  // @@protoc_insertion_point(field_add:amarlon.SpellsData.spell)
  return spell_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::amarlon::SpellData >&
SpellsData::spell() const {
  // @@protoc_insertion_point(field_list:amarlon.SpellsData.spell)
  return spell_;
}
inline ::google::protobuf::RepeatedPtrField< ::amarlon::SpellData >*
SpellsData::mutable_spell() {
  // @@protoc_insertion_point(field_mutable_list:amarlon.SpellsData.spell)
  return &spell_;
}

// -------------------------------------------------------------------

// SpellBookData_SlotData

// required int32 level = 1;
inline bool SpellBookData_SlotData::has_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SpellBookData_SlotData::set_has_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SpellBookData_SlotData::clear_has_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SpellBookData_SlotData::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 SpellBookData_SlotData::level() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellBookData.SlotData.level)
  return level_;
}
inline void SpellBookData_SlotData::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellBookData.SlotData.level)
}

// optional bool isPrepared = 2 [default = false];
inline bool SpellBookData_SlotData::has_isprepared() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SpellBookData_SlotData::set_has_isprepared() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SpellBookData_SlotData::clear_has_isprepared() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SpellBookData_SlotData::clear_isprepared() {
  isprepared_ = false;
  clear_has_isprepared();
}
inline bool SpellBookData_SlotData::isprepared() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellBookData.SlotData.isPrepared)
  return isprepared_;
}
inline void SpellBookData_SlotData::set_isprepared(bool value) {
  set_has_isprepared();
  isprepared_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellBookData.SlotData.isPrepared)
}

// required int32 spell_id = 3;
inline bool SpellBookData_SlotData::has_spell_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SpellBookData_SlotData::set_has_spell_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SpellBookData_SlotData::clear_has_spell_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SpellBookData_SlotData::clear_spell_id() {
  spell_id_ = 0;
  clear_has_spell_id();
}
inline ::google::protobuf::int32 SpellBookData_SlotData::spell_id() const {
  // @@protoc_insertion_point(field_get:amarlon.SpellBookData.SlotData.spell_id)
  return spell_id_;
}
inline void SpellBookData_SlotData::set_spell_id(::google::protobuf::int32 value) {
  set_has_spell_id();
  spell_id_ = value;
  // @@protoc_insertion_point(field_set:amarlon.SpellBookData.SlotData.spell_id)
}

// -------------------------------------------------------------------

// SpellBookData

// repeated int32 knownSpells = 1;
inline int SpellBookData::knownspells_size() const {
  return knownspells_.size();
}
inline void SpellBookData::clear_knownspells() {
  knownspells_.Clear();
}
inline ::google::protobuf::int32 SpellBookData::knownspells(int index) const {
  // @@protoc_insertion_point(field_get:amarlon.SpellBookData.knownSpells)
  return knownspells_.Get(index);
}
inline void SpellBookData::set_knownspells(int index, ::google::protobuf::int32 value) {
  knownspells_.Set(index, value);
  // @@protoc_insertion_point(field_set:amarlon.SpellBookData.knownSpells)
}
inline void SpellBookData::add_knownspells(::google::protobuf::int32 value) {
  knownspells_.Add(value);
  // @@protoc_insertion_point(field_add:amarlon.SpellBookData.knownSpells)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
SpellBookData::knownspells() const {
  // @@protoc_insertion_point(field_list:amarlon.SpellBookData.knownSpells)
  return knownspells_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
SpellBookData::mutable_knownspells() {
  // @@protoc_insertion_point(field_mutable_list:amarlon.SpellBookData.knownSpells)
  return &knownspells_;
}

// repeated .amarlon.SpellBookData.SlotData spellSlots = 2;
inline int SpellBookData::spellslots_size() const {
  return spellslots_.size();
}
inline void SpellBookData::clear_spellslots() {
  spellslots_.Clear();
}
inline const ::amarlon::SpellBookData_SlotData& SpellBookData::spellslots(int index) const {
  // @@protoc_insertion_point(field_get:amarlon.SpellBookData.spellSlots)
  return spellslots_.Get(index);
}
inline ::amarlon::SpellBookData_SlotData* SpellBookData::mutable_spellslots(int index) {
  // @@protoc_insertion_point(field_mutable:amarlon.SpellBookData.spellSlots)
  return spellslots_.Mutable(index);
}
inline ::amarlon::SpellBookData_SlotData* SpellBookData::add_spellslots() {
  // @@protoc_insertion_point(field_add:amarlon.SpellBookData.spellSlots)
  return spellslots_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::amarlon::SpellBookData_SlotData >&
SpellBookData::spellslots() const {
  // @@protoc_insertion_point(field_list:amarlon.SpellBookData.spellSlots)
  return spellslots_;
}
inline ::google::protobuf::RepeatedPtrField< ::amarlon::SpellBookData_SlotData >*
SpellBookData::mutable_spellslots() {
  // @@protoc_insertion_point(field_mutable_list:amarlon.SpellBookData.spellSlots)
  return &spellslots_;
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

#endif  // PROTOBUF_spell_2eproto__INCLUDED