#pragma once

#define DECLARE_SINGLETON(Target)        \
private:\
friend class std::unique_ptr<Target>::deleter_type;      \
friend class std::unique_ptr<Target>;         \
friend class SingleTon<Target>;\
Target();\
virtual ~Target()noexcept;       \

#define DECLARE_DEFAULT_MOVE_COPY(Target)       \
public:\
Target(Target&&)noexcept = default;\
Target& operator=(Target&&)noexcept = default;\
Target(const Target&) = default;\
Target& operator=(const Target&) = default;\

// Singleton
// 이동 카피 삭제 
#define DECLARE_DELETE_MOVE_COPY(Target)   \
public:\
Target(Target&&)noexcept = delete;\
Target& operator=(Target&&)noexcept = delete;\
Target(const Target&) = delete;\
Target& operator=(const Target&) = delete;\

