#pragma once
#include <btBulletDynamicsCommon.h>
#include <unordered_map>
#include <list>
#include <functional>
#include "Log.hpp"

template<typename T>
class ContactHandler {
public:
  template <typename T0, typename T1>
  using Hook = std::function<void (btManifoldPoint &cp, btRigidBody *const rb0, btRigidBody *const rb1, T0 *const, T1 *const)>;
  
private:
  static std::unordered_map<size_t, std::unordered_map<size_t, std::list<Hook<T, T> > > > table_;
public:
  static bool handle(btManifoldPoint &cp, void *body0_, void *body1_) {
    //debug << "ContactHandler::handle()\n";
    auto rb0 = static_cast<btRigidBody *>(body0_);
    auto rb1 = static_cast<btRigidBody *>(body1_);
    auto con0 = static_cast<T *>(rb0->getUserPointer());
    auto con1 = static_cast<T *>(rb1->getUserPointer());
    if (con0 == NULL || con1 == NULL)
      return false;
    //debug << "ContactHandler::handle() " << typeid(*con0).name() << ' ' << typeid(*con1).name() << '\n';
    auto it = table_.find(typeid(*con0).hash_code());
    if (it == table_.end())
      return false;
    auto it0 = it->second.find(typeid(*con1).hash_code());
    if (it0 == it->second.end())
      return false;
    for (auto hook : it0->second)
      hook(cp, rb0, rb1, con0, con1);
    return true;
  }

  static void add(const std::type_info &t0,
                  const std::type_info &t1,
                  Hook<T, T> hook,
                  bool both = true) {
    size_t h0 = t0.hash_code(),
      h1 = t1.hash_code();
    
    table_[h0][h1].push_back(hook);
    if (both && h0 != h1)
      table_[h1][h0].push_back([hook](btManifoldPoint &cp,
                                      btRigidBody *const rb1,
                                      btRigidBody *rb0,
                                      T *const t1, T *const t0) -> void {
                                 hook(cp, rb0, rb1, t0, t1);
                               });
  }
};

template <typename T>
std::unordered_map<size_t, std::unordered_map<size_t, std::list<typename ContactHandler<T>::template Hook<T, T> > > > ContactHandler<T>::table_;
