// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/mocap/mocap.proto)

#include "mocap/mocap.grpc.pb.h"
#include "plugins/mocap/mocap.h"

#include "mavsdk.h"

#include "lazy_plugin.h"

#include "log.h"
#include <atomic>
#include <cmath>
#include <future>
#include <limits>
#include <memory>
#include <mutex>
#include <sstream>
#include <vector>

namespace mavsdk {
namespace mavsdk_server {

template<typename Mocap = Mocap, typename LazyPlugin = LazyPlugin<Mocap>>

class MocapServiceImpl final : public rpc::mocap::MocapService::Service {
public:
    MocapServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}

    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::Mocap::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_mocap_result = new rpc::mocap::MocapResult();
        rpc_mocap_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_mocap_result->set_result_str(ss.str());

        response->set_allocated_mocap_result(rpc_mocap_result);
    }

    static std::unique_ptr<rpc::mocap::PositionBody>
    translateToRpcPositionBody(const mavsdk::Mocap::PositionBody& position_body)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::PositionBody>();

        rpc_obj->set_x_m(position_body.x_m);

        rpc_obj->set_y_m(position_body.y_m);

        rpc_obj->set_z_m(position_body.z_m);

        return rpc_obj;
    }

    static mavsdk::Mocap::PositionBody
    translateFromRpcPositionBody(const rpc::mocap::PositionBody& position_body)
    {
        mavsdk::Mocap::PositionBody obj;

        obj.x_m = position_body.x_m();

        obj.y_m = position_body.y_m();

        obj.z_m = position_body.z_m();

        return obj;
    }

    static std::unique_ptr<rpc::mocap::AngleBody>
    translateToRpcAngleBody(const mavsdk::Mocap::AngleBody& angle_body)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::AngleBody>();

        rpc_obj->set_roll_rad(angle_body.roll_rad);

        rpc_obj->set_pitch_rad(angle_body.pitch_rad);

        rpc_obj->set_yaw_rad(angle_body.yaw_rad);

        return rpc_obj;
    }

    static mavsdk::Mocap::AngleBody
    translateFromRpcAngleBody(const rpc::mocap::AngleBody& angle_body)
    {
        mavsdk::Mocap::AngleBody obj;

        obj.roll_rad = angle_body.roll_rad();

        obj.pitch_rad = angle_body.pitch_rad();

        obj.yaw_rad = angle_body.yaw_rad();

        return obj;
    }

    static std::unique_ptr<rpc::mocap::SpeedBody>
    translateToRpcSpeedBody(const mavsdk::Mocap::SpeedBody& speed_body)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::SpeedBody>();

        rpc_obj->set_x_m_s(speed_body.x_m_s);

        rpc_obj->set_y_m_s(speed_body.y_m_s);

        rpc_obj->set_z_m_s(speed_body.z_m_s);

        return rpc_obj;
    }

    static mavsdk::Mocap::SpeedBody
    translateFromRpcSpeedBody(const rpc::mocap::SpeedBody& speed_body)
    {
        mavsdk::Mocap::SpeedBody obj;

        obj.x_m_s = speed_body.x_m_s();

        obj.y_m_s = speed_body.y_m_s();

        obj.z_m_s = speed_body.z_m_s();

        return obj;
    }

    static std::unique_ptr<rpc::mocap::AngularVelocityBody> translateToRpcAngularVelocityBody(
        const mavsdk::Mocap::AngularVelocityBody& angular_velocity_body)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::AngularVelocityBody>();

        rpc_obj->set_roll_rad_s(angular_velocity_body.roll_rad_s);

        rpc_obj->set_pitch_rad_s(angular_velocity_body.pitch_rad_s);

        rpc_obj->set_yaw_rad_s(angular_velocity_body.yaw_rad_s);

        return rpc_obj;
    }

    static mavsdk::Mocap::AngularVelocityBody translateFromRpcAngularVelocityBody(
        const rpc::mocap::AngularVelocityBody& angular_velocity_body)
    {
        mavsdk::Mocap::AngularVelocityBody obj;

        obj.roll_rad_s = angular_velocity_body.roll_rad_s();

        obj.pitch_rad_s = angular_velocity_body.pitch_rad_s();

        obj.yaw_rad_s = angular_velocity_body.yaw_rad_s();

        return obj;
    }

    static std::unique_ptr<rpc::mocap::Covariance>
    translateToRpcCovariance(const mavsdk::Mocap::Covariance& covariance)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::Covariance>();

        for (const auto& elem : covariance.covariance_matrix) {
            rpc_obj->add_covariance_matrix(elem);
        }

        return rpc_obj;
    }

    static mavsdk::Mocap::Covariance
    translateFromRpcCovariance(const rpc::mocap::Covariance& covariance)
    {
        mavsdk::Mocap::Covariance obj;

        for (const auto& elem : covariance.covariance_matrix()) {
            obj.covariance_matrix.push_back(elem);
        }

        return obj;
    }

    static std::unique_ptr<rpc::mocap::Quaternion>
    translateToRpcQuaternion(const mavsdk::Mocap::Quaternion& quaternion)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::Quaternion>();

        rpc_obj->set_w(quaternion.w);

        rpc_obj->set_x(quaternion.x);

        rpc_obj->set_y(quaternion.y);

        rpc_obj->set_z(quaternion.z);

        return rpc_obj;
    }

    static mavsdk::Mocap::Quaternion
    translateFromRpcQuaternion(const rpc::mocap::Quaternion& quaternion)
    {
        mavsdk::Mocap::Quaternion obj;

        obj.w = quaternion.w();

        obj.x = quaternion.x();

        obj.y = quaternion.y();

        obj.z = quaternion.z();

        return obj;
    }

    static std::unique_ptr<rpc::mocap::VisionPositionEstimate> translateToRpcVisionPositionEstimate(
        const mavsdk::Mocap::VisionPositionEstimate& vision_position_estimate)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::VisionPositionEstimate>();

        rpc_obj->set_time_usec(vision_position_estimate.time_usec);

        rpc_obj->set_allocated_position_body(
            translateToRpcPositionBody(vision_position_estimate.position_body).release());

        rpc_obj->set_allocated_angle_body(
            translateToRpcAngleBody(vision_position_estimate.angle_body).release());

        rpc_obj->set_allocated_pose_covariance(
            translateToRpcCovariance(vision_position_estimate.pose_covariance).release());

        return rpc_obj;
    }

    static mavsdk::Mocap::VisionPositionEstimate translateFromRpcVisionPositionEstimate(
        const rpc::mocap::VisionPositionEstimate& vision_position_estimate)
    {
        mavsdk::Mocap::VisionPositionEstimate obj;

        obj.time_usec = vision_position_estimate.time_usec();

        obj.position_body = translateFromRpcPositionBody(vision_position_estimate.position_body());

        obj.angle_body = translateFromRpcAngleBody(vision_position_estimate.angle_body());

        obj.pose_covariance =
            translateFromRpcCovariance(vision_position_estimate.pose_covariance());

        return obj;
    }

    static std::unique_ptr<rpc::mocap::AttitudePositionMocap> translateToRpcAttitudePositionMocap(
        const mavsdk::Mocap::AttitudePositionMocap& attitude_position_mocap)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::AttitudePositionMocap>();

        rpc_obj->set_time_usec(attitude_position_mocap.time_usec);

        rpc_obj->set_allocated_q(translateToRpcQuaternion(attitude_position_mocap.q).release());

        rpc_obj->set_allocated_position_body(
            translateToRpcPositionBody(attitude_position_mocap.position_body).release());

        rpc_obj->set_allocated_pose_covariance(
            translateToRpcCovariance(attitude_position_mocap.pose_covariance).release());

        return rpc_obj;
    }

    static mavsdk::Mocap::AttitudePositionMocap translateFromRpcAttitudePositionMocap(
        const rpc::mocap::AttitudePositionMocap& attitude_position_mocap)
    {
        mavsdk::Mocap::AttitudePositionMocap obj;

        obj.time_usec = attitude_position_mocap.time_usec();

        obj.q = translateFromRpcQuaternion(attitude_position_mocap.q());

        obj.position_body = translateFromRpcPositionBody(attitude_position_mocap.position_body());

        obj.pose_covariance = translateFromRpcCovariance(attitude_position_mocap.pose_covariance());

        return obj;
    }

    static rpc::mocap::Odometry::MavFrame
    translateToRpcMavFrame(const mavsdk::Mocap::Odometry::MavFrame& mav_frame)
    {
        switch (mav_frame) {
            default:
                LogErr() << "Unknown mav_frame enum value: " << static_cast<int>(mav_frame);
            // FALLTHROUGH
            case mavsdk::Mocap::Odometry::MavFrame::MocapNed:
                return rpc::mocap::Odometry_MavFrame_MAV_FRAME_MOCAP_NED;
            case mavsdk::Mocap::Odometry::MavFrame::LocalFrd:
                return rpc::mocap::Odometry_MavFrame_MAV_FRAME_LOCAL_FRD;
        }
    }

    static mavsdk::Mocap::Odometry::MavFrame
    translateFromRpcMavFrame(const rpc::mocap::Odometry::MavFrame mav_frame)
    {
        switch (mav_frame) {
            default:
                LogErr() << "Unknown mav_frame enum value: " << static_cast<int>(mav_frame);
            // FALLTHROUGH
            case rpc::mocap::Odometry_MavFrame_MAV_FRAME_MOCAP_NED:
                return mavsdk::Mocap::Odometry::MavFrame::MocapNed;
            case rpc::mocap::Odometry_MavFrame_MAV_FRAME_LOCAL_FRD:
                return mavsdk::Mocap::Odometry::MavFrame::LocalFrd;
        }
    }

    static std::unique_ptr<rpc::mocap::Odometry>
    translateToRpcOdometry(const mavsdk::Mocap::Odometry& odometry)
    {
        auto rpc_obj = std::make_unique<rpc::mocap::Odometry>();

        rpc_obj->set_time_usec(odometry.time_usec);

        rpc_obj->set_frame_id(translateToRpcMavFrame(odometry.frame_id));

        rpc_obj->set_allocated_position_body(
            translateToRpcPositionBody(odometry.position_body).release());

        rpc_obj->set_allocated_q(translateToRpcQuaternion(odometry.q).release());

        rpc_obj->set_allocated_speed_body(translateToRpcSpeedBody(odometry.speed_body).release());

        rpc_obj->set_allocated_angular_velocity_body(
            translateToRpcAngularVelocityBody(odometry.angular_velocity_body).release());

        rpc_obj->set_allocated_pose_covariance(
            translateToRpcCovariance(odometry.pose_covariance).release());

        rpc_obj->set_allocated_velocity_covariance(
            translateToRpcCovariance(odometry.velocity_covariance).release());

        return rpc_obj;
    }

    static mavsdk::Mocap::Odometry translateFromRpcOdometry(const rpc::mocap::Odometry& odometry)
    {
        mavsdk::Mocap::Odometry obj;

        obj.time_usec = odometry.time_usec();

        obj.frame_id = translateFromRpcMavFrame(odometry.frame_id());

        obj.position_body = translateFromRpcPositionBody(odometry.position_body());

        obj.q = translateFromRpcQuaternion(odometry.q());

        obj.speed_body = translateFromRpcSpeedBody(odometry.speed_body());

        obj.angular_velocity_body =
            translateFromRpcAngularVelocityBody(odometry.angular_velocity_body());

        obj.pose_covariance = translateFromRpcCovariance(odometry.pose_covariance());

        obj.velocity_covariance = translateFromRpcCovariance(odometry.velocity_covariance());

        return obj;
    }

    static rpc::mocap::MocapResult::Result translateToRpcResult(const mavsdk::Mocap::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::Mocap::Result::Unknown:
                return rpc::mocap::MocapResult_Result_RESULT_UNKNOWN;
            case mavsdk::Mocap::Result::Success:
                return rpc::mocap::MocapResult_Result_RESULT_SUCCESS;
            case mavsdk::Mocap::Result::NoSystem:
                return rpc::mocap::MocapResult_Result_RESULT_NO_SYSTEM;
            case mavsdk::Mocap::Result::ConnectionError:
                return rpc::mocap::MocapResult_Result_RESULT_CONNECTION_ERROR;
            case mavsdk::Mocap::Result::InvalidRequestData:
                return rpc::mocap::MocapResult_Result_RESULT_INVALID_REQUEST_DATA;
            case mavsdk::Mocap::Result::Unsupported:
                return rpc::mocap::MocapResult_Result_RESULT_UNSUPPORTED;
        }
    }

    static mavsdk::Mocap::Result
    translateFromRpcResult(const rpc::mocap::MocapResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::mocap::MocapResult_Result_RESULT_UNKNOWN:
                return mavsdk::Mocap::Result::Unknown;
            case rpc::mocap::MocapResult_Result_RESULT_SUCCESS:
                return mavsdk::Mocap::Result::Success;
            case rpc::mocap::MocapResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::Mocap::Result::NoSystem;
            case rpc::mocap::MocapResult_Result_RESULT_CONNECTION_ERROR:
                return mavsdk::Mocap::Result::ConnectionError;
            case rpc::mocap::MocapResult_Result_RESULT_INVALID_REQUEST_DATA:
                return mavsdk::Mocap::Result::InvalidRequestData;
            case rpc::mocap::MocapResult_Result_RESULT_UNSUPPORTED:
                return mavsdk::Mocap::Result::Unsupported;
        }
    }

    grpc::Status SetVisionPositionEstimate(
        grpc::ServerContext* /* context */,
        const rpc::mocap::SetVisionPositionEstimateRequest* request,
        rpc::mocap::SetVisionPositionEstimateResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Mocap::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetVisionPositionEstimate sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_vision_position_estimate(
            translateFromRpcVisionPositionEstimate(request->vision_position_estimate()));

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetAttitudePositionMocap(
        grpc::ServerContext* /* context */,
        const rpc::mocap::SetAttitudePositionMocapRequest* request,
        rpc::mocap::SetAttitudePositionMocapResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Mocap::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetAttitudePositionMocap sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_attitude_position_mocap(
            translateFromRpcAttitudePositionMocap(request->attitude_position_mocap()));

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetOdometry(
        grpc::ServerContext* /* context */,
        const rpc::mocap::SetOdometryRequest* request,
        rpc::mocap::SetOdometryResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Mocap::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetOdometry sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_odometry(
            translateFromRpcOdometry(request->odometry()));

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    void stop()
    {
        _stopped.store(true);
        std::lock_guard<std::mutex> lock(_stream_stop_mutex);
        for (auto& prom : _stream_stop_promises) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        }
    }

private:
    void register_stream_stop_promise(std::weak_ptr<std::promise<void>> prom)
    {
        // If we have already stopped, set promise immediately and don't add it to list.
        if (_stopped.load()) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        } else {
            std::lock_guard<std::mutex> lock(_stream_stop_mutex);
            _stream_stop_promises.push_back(prom);
        }
    }

    void unregister_stream_stop_promise(std::shared_ptr<std::promise<void>> prom)
    {
        std::lock_guard<std::mutex> lock(_stream_stop_mutex);
        for (auto it = _stream_stop_promises.begin(); it != _stream_stop_promises.end();
             /* ++it */) {
            if (it->lock() == prom) {
                it = _stream_stop_promises.erase(it);
            } else {
                ++it;
            }
        }
    }

    LazyPlugin& _lazy_plugin;

    std::atomic<bool> _stopped{false};
    std::mutex _stream_stop_mutex{};
    std::vector<std::weak_ptr<std::promise<void>>> _stream_stop_promises{};
};

} // namespace mavsdk_server
} // namespace mavsdk