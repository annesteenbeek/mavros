/**
 * @brief Tank level plugin
 * @file tank_level.cpp
 * @author Anne Steenbeek <annesteenbeek@gmail.com>
 */

#include <mavros/mavros_plugin.h>
#include <pluginlib/class_list_macros.h>
#include <mavros_msgs/TankLevel.h>

namespace mavplugin {
/**
 * @brief tank level plugin
 *
 * broadcast the level of the spray tank connected to the companion computer
 */
class TankLevelPlugin : public MavRosPlugin{
public:
    TankLevelPlugin():
        tl_nh("~tank_level"),
        uas(nullptr)
    { };

    void initialize(UAS &uas_) {
        uas = &uas_;

        tank_level_sub = tl_nh.subscribe("tank_level", 10, &TankLevelPlugin::tank_level_cb, this);
    }

    const message_map get_rx_handlers() {
        return { /* Rx disabled */ };
    }

private:
    ros::NodeHandle tl_nh;
    UAS *uas;

    ros::Subscriber tank_level_sub;


    void tank_level_cb(const mavros_msgs::TankLevel::ConstPtr &req) {
        set_tank_level(req->percentage, req->raw);
        }

    void set_tank_level(const uint8_t percentage, const uint32_t raw) {

        mavlink_message_t msg;

        const uint8_t tgt_sys_id = 0;
        const uint8_t tgt_comp_id = 0;

        /* mavlink_msg_tank_level_pack_chan( */
        /*         UAS_PACK_CHAN(uas), */
        /*         &msg, */
        /*         tgt_sys_id, */
        /*         tgt_comp_id, */
        /*         percentage, */
        /*         raw); */
        /* UAS_FCU(uas)->send_message(&msg); */
        }
}; // TankLevelPlugin    
}; // namespace mavplugin

PLUGINLIB_EXPORT_CLASS(mavplugin::TankLevelPlugin, mavplugin::MavRosPlugin)
