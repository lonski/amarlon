// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tile.proto

#ifndef PROTOBUF_tile_2eproto__INCLUDED
#define PROTOBUF_tile_2eproto__INCLUDED

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
void  protobuf_AddDesc_tile_2eproto();
void protobuf_AssignDesc_tile_2eproto();
void protobuf_ShutdownFile_tile_2eproto();

class TileData;
class TilesData;
class TileState;

// ===================================================================

class TileData : public ::google::protobuf::Message {
 public:
  TileData();
  virtual ~TileData();

  TileData(const TileData& from);

  inline TileData& operator=(const TileData& from) {
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
  static const TileData& default_instance();

  void Swap(TileData* other);

  // implements Message ----------------------------------------------

  TileData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TileData& from);
  void MergeFrom(const TileData& from);
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

  // required string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional bool transparent = 3 [default = false];
  inline bool has_transparent() const;
  inline void clear_transparent();
  static const int kTransparentFieldNumber = 3;
  inline bool transparent() const;
  inline void set_transparent(bool value);

  // required string color = 4;
  inline bool has_color() const;
  inline void clear_color();
  static const int kColorFieldNumber = 4;
  inline const ::std::string& color() const;
  inline void set_color(const ::std::string& value);
  inline void set_color(const char* value);
  inline void set_color(const char* value, size_t size);
  inline ::std::string* mutable_color();
  inline ::std::string* release_color();
  inline void set_allocated_color(::std::string* color);

  // optional bool walkable = 5 [default = false];
  inline bool has_walkable() const;
  inline void clear_walkable();
  static const int kWalkableFieldNumber = 5;
  inline bool walkable() const;
  inline void set_walkable(bool value);

  // required string character = 6;
  inline bool has_character() const;
  inline void clear_character();
  static const int kCharacterFieldNumber = 6;
  inline const ::std::string& character() const;
  inline void set_character(const ::std::string& value);
  inline void set_character(const char* value);
  inline void set_character(const char* value, size_t size);
  inline ::std::string* mutable_character();
  inline ::std::string* release_character();
  inline void set_allocated_character(::std::string* character);

  // @@protoc_insertion_point(class_scope:amarlon.TileData)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_transparent();
  inline void clear_has_transparent();
  inline void set_has_color();
  inline void clear_has_color();
  inline void set_has_walkable();
  inline void clear_has_walkable();
  inline void set_has_character();
  inline void clear_has_character();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  ::google::protobuf::int32 id_;
  bool transparent_;
  bool walkable_;
  ::std::string* color_;
  ::std::string* character_;
  friend void  protobuf_AddDesc_tile_2eproto();
  friend void protobuf_AssignDesc_tile_2eproto();
  friend void protobuf_ShutdownFile_tile_2eproto();

  void InitAsDefaultInstance();
  static TileData* default_instance_;
};
// -------------------------------------------------------------------

class TilesData : public ::google::protobuf::Message {
 public:
  TilesData();
  virtual ~TilesData();

  TilesData(const TilesData& from);

  inline TilesData& operator=(const TilesData& from) {
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
  static const TilesData& default_instance();

  void Swap(TilesData* other);

  // implements Message ----------------------------------------------

  TilesData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TilesData& from);
  void MergeFrom(const TilesData& from);
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

  // repeated .amarlon.TileData tile = 1;
  inline int tile_size() const;
  inline void clear_tile();
  static const int kTileFieldNumber = 1;
  inline const ::amarlon::TileData& tile(int index) const;
  inline ::amarlon::TileData* mutable_tile(int index);
  inline ::amarlon::TileData* add_tile();
  inline const ::google::protobuf::RepeatedPtrField< ::amarlon::TileData >&
      tile() const;
  inline ::google::protobuf::RepeatedPtrField< ::amarlon::TileData >*
      mutable_tile();

  // @@protoc_insertion_point(class_scope:amarlon.TilesData)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::amarlon::TileData > tile_;
  friend void  protobuf_AddDesc_tile_2eproto();
  friend void protobuf_AssignDesc_tile_2eproto();
  friend void protobuf_ShutdownFile_tile_2eproto();

  void InitAsDefaultInstance();
  static TilesData* default_instance_;
};
// -------------------------------------------------------------------

class TileState : public ::google::protobuf::Message {
 public:
  TileState();
  virtual ~TileState();

  TileState(const TileState& from);

  inline TileState& operator=(const TileState& from) {
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
  static const TileState& default_instance();

  void Swap(TileState* other);

  // implements Message ----------------------------------------------

  TileState* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TileState& from);
  void MergeFrom(const TileState& from);
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

  // required int32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);

  // required fixed32 flags = 2;
  inline bool has_flags() const;
  inline void clear_flags();
  static const int kFlagsFieldNumber = 2;
  inline ::google::protobuf::uint32 flags() const;
  inline void set_flags(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:amarlon.TileState)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_flags();
  inline void clear_has_flags();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 type_;
  ::google::protobuf::uint32 flags_;
  friend void  protobuf_AddDesc_tile_2eproto();
  friend void protobuf_AssignDesc_tile_2eproto();
  friend void protobuf_ShutdownFile_tile_2eproto();

  void InitAsDefaultInstance();
  static TileState* default_instance_;
};
// ===================================================================


// ===================================================================

// TileData

// required int32 id = 1;
inline bool TileData::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TileData::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TileData::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TileData::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 TileData::id() const {
  // @@protoc_insertion_point(field_get:amarlon.TileData.id)
  return id_;
}
inline void TileData::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:amarlon.TileData.id)
}

// required string name = 2;
inline bool TileData::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TileData::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TileData::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TileData::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& TileData::name() const {
  // @@protoc_insertion_point(field_get:amarlon.TileData.name)
  return *name_;
}
inline void TileData::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:amarlon.TileData.name)
}
inline void TileData::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:amarlon.TileData.name)
}
inline void TileData::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:amarlon.TileData.name)
}
inline ::std::string* TileData::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:amarlon.TileData.name)
  return name_;
}
inline ::std::string* TileData::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TileData::set_allocated_name(::std::string* name) {
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
  // @@protoc_insertion_point(field_set_allocated:amarlon.TileData.name)
}

// optional bool transparent = 3 [default = false];
inline bool TileData::has_transparent() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TileData::set_has_transparent() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TileData::clear_has_transparent() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TileData::clear_transparent() {
  transparent_ = false;
  clear_has_transparent();
}
inline bool TileData::transparent() const {
  // @@protoc_insertion_point(field_get:amarlon.TileData.transparent)
  return transparent_;
}
inline void TileData::set_transparent(bool value) {
  set_has_transparent();
  transparent_ = value;
  // @@protoc_insertion_point(field_set:amarlon.TileData.transparent)
}

// required string color = 4;
inline bool TileData::has_color() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TileData::set_has_color() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TileData::clear_has_color() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TileData::clear_color() {
  if (color_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    color_->clear();
  }
  clear_has_color();
}
inline const ::std::string& TileData::color() const {
  // @@protoc_insertion_point(field_get:amarlon.TileData.color)
  return *color_;
}
inline void TileData::set_color(const ::std::string& value) {
  set_has_color();
  if (color_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    color_ = new ::std::string;
  }
  color_->assign(value);
  // @@protoc_insertion_point(field_set:amarlon.TileData.color)
}
inline void TileData::set_color(const char* value) {
  set_has_color();
  if (color_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    color_ = new ::std::string;
  }
  color_->assign(value);
  // @@protoc_insertion_point(field_set_char:amarlon.TileData.color)
}
inline void TileData::set_color(const char* value, size_t size) {
  set_has_color();
  if (color_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    color_ = new ::std::string;
  }
  color_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:amarlon.TileData.color)
}
inline ::std::string* TileData::mutable_color() {
  set_has_color();
  if (color_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    color_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:amarlon.TileData.color)
  return color_;
}
inline ::std::string* TileData::release_color() {
  clear_has_color();
  if (color_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = color_;
    color_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TileData::set_allocated_color(::std::string* color) {
  if (color_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete color_;
  }
  if (color) {
    set_has_color();
    color_ = color;
  } else {
    clear_has_color();
    color_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:amarlon.TileData.color)
}

// optional bool walkable = 5 [default = false];
inline bool TileData::has_walkable() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void TileData::set_has_walkable() {
  _has_bits_[0] |= 0x00000010u;
}
inline void TileData::clear_has_walkable() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void TileData::clear_walkable() {
  walkable_ = false;
  clear_has_walkable();
}
inline bool TileData::walkable() const {
  // @@protoc_insertion_point(field_get:amarlon.TileData.walkable)
  return walkable_;
}
inline void TileData::set_walkable(bool value) {
  set_has_walkable();
  walkable_ = value;
  // @@protoc_insertion_point(field_set:amarlon.TileData.walkable)
}

// required string character = 6;
inline bool TileData::has_character() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void TileData::set_has_character() {
  _has_bits_[0] |= 0x00000020u;
}
inline void TileData::clear_has_character() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void TileData::clear_character() {
  if (character_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    character_->clear();
  }
  clear_has_character();
}
inline const ::std::string& TileData::character() const {
  // @@protoc_insertion_point(field_get:amarlon.TileData.character)
  return *character_;
}
inline void TileData::set_character(const ::std::string& value) {
  set_has_character();
  if (character_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    character_ = new ::std::string;
  }
  character_->assign(value);
  // @@protoc_insertion_point(field_set:amarlon.TileData.character)
}
inline void TileData::set_character(const char* value) {
  set_has_character();
  if (character_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    character_ = new ::std::string;
  }
  character_->assign(value);
  // @@protoc_insertion_point(field_set_char:amarlon.TileData.character)
}
inline void TileData::set_character(const char* value, size_t size) {
  set_has_character();
  if (character_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    character_ = new ::std::string;
  }
  character_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:amarlon.TileData.character)
}
inline ::std::string* TileData::mutable_character() {
  set_has_character();
  if (character_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    character_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:amarlon.TileData.character)
  return character_;
}
inline ::std::string* TileData::release_character() {
  clear_has_character();
  if (character_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = character_;
    character_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TileData::set_allocated_character(::std::string* character) {
  if (character_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete character_;
  }
  if (character) {
    set_has_character();
    character_ = character;
  } else {
    clear_has_character();
    character_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:amarlon.TileData.character)
}

// -------------------------------------------------------------------

// TilesData

// repeated .amarlon.TileData tile = 1;
inline int TilesData::tile_size() const {
  return tile_.size();
}
inline void TilesData::clear_tile() {
  tile_.Clear();
}
inline const ::amarlon::TileData& TilesData::tile(int index) const {
  // @@protoc_insertion_point(field_get:amarlon.TilesData.tile)
  return tile_.Get(index);
}
inline ::amarlon::TileData* TilesData::mutable_tile(int index) {
  // @@protoc_insertion_point(field_mutable:amarlon.TilesData.tile)
  return tile_.Mutable(index);
}
inline ::amarlon::TileData* TilesData::add_tile() {
  // @@protoc_insertion_point(field_add:amarlon.TilesData.tile)
  return tile_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::amarlon::TileData >&
TilesData::tile() const {
  // @@protoc_insertion_point(field_list:amarlon.TilesData.tile)
  return tile_;
}
inline ::google::protobuf::RepeatedPtrField< ::amarlon::TileData >*
TilesData::mutable_tile() {
  // @@protoc_insertion_point(field_mutable_list:amarlon.TilesData.tile)
  return &tile_;
}

// -------------------------------------------------------------------

// TileState

// required int32 type = 1;
inline bool TileState::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TileState::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TileState::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TileState::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 TileState::type() const {
  // @@protoc_insertion_point(field_get:amarlon.TileState.type)
  return type_;
}
inline void TileState::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:amarlon.TileState.type)
}

// required fixed32 flags = 2;
inline bool TileState::has_flags() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TileState::set_has_flags() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TileState::clear_has_flags() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TileState::clear_flags() {
  flags_ = 0u;
  clear_has_flags();
}
inline ::google::protobuf::uint32 TileState::flags() const {
  // @@protoc_insertion_point(field_get:amarlon.TileState.flags)
  return flags_;
}
inline void TileState::set_flags(::google::protobuf::uint32 value) {
  set_has_flags();
  flags_ = value;
  // @@protoc_insertion_point(field_set:amarlon.TileState.flags)
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

#endif  // PROTOBUF_tile_2eproto__INCLUDED