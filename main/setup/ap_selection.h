#ifndef B24B21E0_30DA_4083_A2D3_F80A82371EA0
#define B24B21E0_30DA_4083_A2D3_F80A82371EA0

#include <wifi_scan_visitor.h>

#include <string>
#include <vector>

class ap_selection final : public wifi_scan_visitor {
 public:
  bool continue_with_result(const wifi_scan_result& result) override;
  void flush();
  const std::string& get_selected_ssid() const noexcept;

 private:
  void user_select(bool expect_more);
  std::vector<std::string> ssids;
  std::string selected_ssid;
  bool stop;
};

#endif /* B24B21E0_30DA_4083_A2D3_F80A82371EA0 */
