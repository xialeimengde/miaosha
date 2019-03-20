// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: miaosha.proto

#ifndef PROTOBUF_INCLUDED_miaosha_2eproto
#define PROTOBUF_INCLUDED_miaosha_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_miaosha_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_miaosha_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_miaosha_2eproto();
namespace miaosha {
class MiaoshaRequest;
class MiaoshaRequestDefaultTypeInternal;
extern MiaoshaRequestDefaultTypeInternal _MiaoshaRequest_default_instance_;
class MiaoshaResponse;
class MiaoshaResponseDefaultTypeInternal;
extern MiaoshaResponseDefaultTypeInternal _MiaoshaResponse_default_instance_;
}  // namespace miaosha
namespace google {
namespace protobuf {
template<> ::miaosha::MiaoshaRequest* Arena::CreateMaybeMessage<::miaosha::MiaoshaRequest>(Arena*);
template<> ::miaosha::MiaoshaResponse* Arena::CreateMaybeMessage<::miaosha::MiaoshaResponse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace miaosha {

// ===================================================================

class MiaoshaRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:miaosha.MiaoshaRequest) */ {
 public:
  MiaoshaRequest();
  virtual ~MiaoshaRequest();

  MiaoshaRequest(const MiaoshaRequest& from);

  inline MiaoshaRequest& operator=(const MiaoshaRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MiaoshaRequest(MiaoshaRequest&& from) noexcept
    : MiaoshaRequest() {
    *this = ::std::move(from);
  }

  inline MiaoshaRequest& operator=(MiaoshaRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const MiaoshaRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MiaoshaRequest* internal_default_instance() {
    return reinterpret_cast<const MiaoshaRequest*>(
               &_MiaoshaRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(MiaoshaRequest* other);
  friend void swap(MiaoshaRequest& a, MiaoshaRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MiaoshaRequest* New() const final {
    return CreateMaybeMessage<MiaoshaRequest>(nullptr);
  }

  MiaoshaRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<MiaoshaRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const MiaoshaRequest& from);
  void MergeFrom(const MiaoshaRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MiaoshaRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string user_openid = 1;
  void clear_user_openid();
  static const int kUserOpenidFieldNumber = 1;
  const ::std::string& user_openid() const;
  void set_user_openid(const ::std::string& value);
  #if LANG_CXX11
  void set_user_openid(::std::string&& value);
  #endif
  void set_user_openid(const char* value);
  void set_user_openid(const char* value, size_t size);
  ::std::string* mutable_user_openid();
  ::std::string* release_user_openid();
  void set_allocated_user_openid(::std::string* user_openid);

  // string user_session = 2;
  void clear_user_session();
  static const int kUserSessionFieldNumber = 2;
  const ::std::string& user_session() const;
  void set_user_session(const ::std::string& value);
  #if LANG_CXX11
  void set_user_session(::std::string&& value);
  #endif
  void set_user_session(const char* value);
  void set_user_session(const char* value, size_t size);
  ::std::string* mutable_user_session();
  ::std::string* release_user_session();
  void set_allocated_user_session(::std::string* user_session);

  // @@protoc_insertion_point(class_scope:miaosha.MiaoshaRequest)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr user_openid_;
  ::google::protobuf::internal::ArenaStringPtr user_session_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_miaosha_2eproto;
};
// -------------------------------------------------------------------

class MiaoshaResponse final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:miaosha.MiaoshaResponse) */ {
 public:
  MiaoshaResponse();
  virtual ~MiaoshaResponse();

  MiaoshaResponse(const MiaoshaResponse& from);

  inline MiaoshaResponse& operator=(const MiaoshaResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MiaoshaResponse(MiaoshaResponse&& from) noexcept
    : MiaoshaResponse() {
    *this = ::std::move(from);
  }

  inline MiaoshaResponse& operator=(MiaoshaResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const MiaoshaResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MiaoshaResponse* internal_default_instance() {
    return reinterpret_cast<const MiaoshaResponse*>(
               &_MiaoshaResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(MiaoshaResponse* other);
  friend void swap(MiaoshaResponse& a, MiaoshaResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MiaoshaResponse* New() const final {
    return CreateMaybeMessage<MiaoshaResponse>(nullptr);
  }

  MiaoshaResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<MiaoshaResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const MiaoshaResponse& from);
  void MergeFrom(const MiaoshaResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MiaoshaResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string result = 1;
  void clear_result();
  static const int kResultFieldNumber = 1;
  const ::std::string& result() const;
  void set_result(const ::std::string& value);
  #if LANG_CXX11
  void set_result(::std::string&& value);
  #endif
  void set_result(const char* value);
  void set_result(const char* value, size_t size);
  ::std::string* mutable_result();
  ::std::string* release_result();
  void set_allocated_result(::std::string* result);

  // string ret_msg = 2;
  void clear_ret_msg();
  static const int kRetMsgFieldNumber = 2;
  const ::std::string& ret_msg() const;
  void set_ret_msg(const ::std::string& value);
  #if LANG_CXX11
  void set_ret_msg(::std::string&& value);
  #endif
  void set_ret_msg(const char* value);
  void set_ret_msg(const char* value, size_t size);
  ::std::string* mutable_ret_msg();
  ::std::string* release_ret_msg();
  void set_allocated_ret_msg(::std::string* ret_msg);

  // @@protoc_insertion_point(class_scope:miaosha.MiaoshaResponse)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr result_;
  ::google::protobuf::internal::ArenaStringPtr ret_msg_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_miaosha_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MiaoshaRequest

// string user_openid = 1;
inline void MiaoshaRequest::clear_user_openid() {
  user_openid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MiaoshaRequest::user_openid() const {
  // @@protoc_insertion_point(field_get:miaosha.MiaoshaRequest.user_openid)
  return user_openid_.GetNoArena();
}
inline void MiaoshaRequest::set_user_openid(const ::std::string& value) {
  
  user_openid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:miaosha.MiaoshaRequest.user_openid)
}
#if LANG_CXX11
inline void MiaoshaRequest::set_user_openid(::std::string&& value) {
  
  user_openid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:miaosha.MiaoshaRequest.user_openid)
}
#endif
inline void MiaoshaRequest::set_user_openid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  user_openid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:miaosha.MiaoshaRequest.user_openid)
}
inline void MiaoshaRequest::set_user_openid(const char* value, size_t size) {
  
  user_openid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:miaosha.MiaoshaRequest.user_openid)
}
inline ::std::string* MiaoshaRequest::mutable_user_openid() {
  
  // @@protoc_insertion_point(field_mutable:miaosha.MiaoshaRequest.user_openid)
  return user_openid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MiaoshaRequest::release_user_openid() {
  // @@protoc_insertion_point(field_release:miaosha.MiaoshaRequest.user_openid)
  
  return user_openid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MiaoshaRequest::set_allocated_user_openid(::std::string* user_openid) {
  if (user_openid != nullptr) {
    
  } else {
    
  }
  user_openid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user_openid);
  // @@protoc_insertion_point(field_set_allocated:miaosha.MiaoshaRequest.user_openid)
}

// string user_session = 2;
inline void MiaoshaRequest::clear_user_session() {
  user_session_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MiaoshaRequest::user_session() const {
  // @@protoc_insertion_point(field_get:miaosha.MiaoshaRequest.user_session)
  return user_session_.GetNoArena();
}
inline void MiaoshaRequest::set_user_session(const ::std::string& value) {
  
  user_session_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:miaosha.MiaoshaRequest.user_session)
}
#if LANG_CXX11
inline void MiaoshaRequest::set_user_session(::std::string&& value) {
  
  user_session_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:miaosha.MiaoshaRequest.user_session)
}
#endif
inline void MiaoshaRequest::set_user_session(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  user_session_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:miaosha.MiaoshaRequest.user_session)
}
inline void MiaoshaRequest::set_user_session(const char* value, size_t size) {
  
  user_session_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:miaosha.MiaoshaRequest.user_session)
}
inline ::std::string* MiaoshaRequest::mutable_user_session() {
  
  // @@protoc_insertion_point(field_mutable:miaosha.MiaoshaRequest.user_session)
  return user_session_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MiaoshaRequest::release_user_session() {
  // @@protoc_insertion_point(field_release:miaosha.MiaoshaRequest.user_session)
  
  return user_session_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MiaoshaRequest::set_allocated_user_session(::std::string* user_session) {
  if (user_session != nullptr) {
    
  } else {
    
  }
  user_session_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user_session);
  // @@protoc_insertion_point(field_set_allocated:miaosha.MiaoshaRequest.user_session)
}

// -------------------------------------------------------------------

// MiaoshaResponse

// string result = 1;
inline void MiaoshaResponse::clear_result() {
  result_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MiaoshaResponse::result() const {
  // @@protoc_insertion_point(field_get:miaosha.MiaoshaResponse.result)
  return result_.GetNoArena();
}
inline void MiaoshaResponse::set_result(const ::std::string& value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:miaosha.MiaoshaResponse.result)
}
#if LANG_CXX11
inline void MiaoshaResponse::set_result(::std::string&& value) {
  
  result_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:miaosha.MiaoshaResponse.result)
}
#endif
inline void MiaoshaResponse::set_result(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:miaosha.MiaoshaResponse.result)
}
inline void MiaoshaResponse::set_result(const char* value, size_t size) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:miaosha.MiaoshaResponse.result)
}
inline ::std::string* MiaoshaResponse::mutable_result() {
  
  // @@protoc_insertion_point(field_mutable:miaosha.MiaoshaResponse.result)
  return result_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MiaoshaResponse::release_result() {
  // @@protoc_insertion_point(field_release:miaosha.MiaoshaResponse.result)
  
  return result_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MiaoshaResponse::set_allocated_result(::std::string* result) {
  if (result != nullptr) {
    
  } else {
    
  }
  result_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), result);
  // @@protoc_insertion_point(field_set_allocated:miaosha.MiaoshaResponse.result)
}

// string ret_msg = 2;
inline void MiaoshaResponse::clear_ret_msg() {
  ret_msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MiaoshaResponse::ret_msg() const {
  // @@protoc_insertion_point(field_get:miaosha.MiaoshaResponse.ret_msg)
  return ret_msg_.GetNoArena();
}
inline void MiaoshaResponse::set_ret_msg(const ::std::string& value) {
  
  ret_msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:miaosha.MiaoshaResponse.ret_msg)
}
#if LANG_CXX11
inline void MiaoshaResponse::set_ret_msg(::std::string&& value) {
  
  ret_msg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:miaosha.MiaoshaResponse.ret_msg)
}
#endif
inline void MiaoshaResponse::set_ret_msg(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  ret_msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:miaosha.MiaoshaResponse.ret_msg)
}
inline void MiaoshaResponse::set_ret_msg(const char* value, size_t size) {
  
  ret_msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:miaosha.MiaoshaResponse.ret_msg)
}
inline ::std::string* MiaoshaResponse::mutable_ret_msg() {
  
  // @@protoc_insertion_point(field_mutable:miaosha.MiaoshaResponse.ret_msg)
  return ret_msg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MiaoshaResponse::release_ret_msg() {
  // @@protoc_insertion_point(field_release:miaosha.MiaoshaResponse.ret_msg)
  
  return ret_msg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MiaoshaResponse::set_allocated_ret_msg(::std::string* ret_msg) {
  if (ret_msg != nullptr) {
    
  } else {
    
  }
  ret_msg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ret_msg);
  // @@protoc_insertion_point(field_set_allocated:miaosha.MiaoshaResponse.ret_msg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace miaosha

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_miaosha_2eproto
