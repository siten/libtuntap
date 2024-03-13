#pragma once
#ifndef LIBTUNTAP_ALY0MA60
#define LIBTUNTAP_ALY0MA60

#include <string>
#include <memory>

#include <tuntap.h>

namespace tuntap {

class tuntap
{
 public:
  tuntap(int, int = TUNTAP_ID_ANY);
  tuntap(tuntap const &) = delete;
  tuntap & operator = (tuntap const &) = delete;
  tuntap(tuntap &&) noexcept;

  // Properties
  std::string name() const noexcept;
  void name(std::string const &);
  int mtu() const noexcept;
  void mtu(int);
  t_tun native_handle() const noexcept;

  // Network
  void up();
  void down();
  void ip(std::string const &presentation, int netmask);

  //IO
  int read(void *buf, size_t len) noexcept;
  int write(void *buf, size_t len) noexcept;

  // System
  void release() noexcept;
  void nonblocking(bool);
 private:
  class TunTapDestroyer final {
      public:
          void operator()(device * dev) const noexcept {
              if (dev)
                  ::tuntap_destroy(dev);
          }
  };
  std::unique_ptr<device, TunTapDestroyer> _dev;
};

} /* tuntap */


#endif /* end of include guard: LIBTUNTAP_ALY0MA60 */
