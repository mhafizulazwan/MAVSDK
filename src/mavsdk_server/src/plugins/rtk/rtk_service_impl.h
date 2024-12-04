// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/rtk/rtk.proto)

#include "rtk/rtk.grpc.pb.h"
#include "plugins/rtk/rtk.h"

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

template<typename Rtk = Rtk, typename LazyPlugin = LazyPlugin<Rtk>>

class RtkServiceImpl final : public rpc::rtk::RtkService::Service {
public:
    RtkServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}

    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::Rtk::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_rtk_result = new rpc::rtk::RtkResult();
        rpc_rtk_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_rtk_result->set_result_str(ss.str());

        response->set_allocated_rtk_result(rpc_rtk_result);
    }

    static std::unique_ptr<rpc::rtk::RtcmData>
    translateToRpcRtcmData(const mavsdk::Rtk::RtcmData& rtcm_data)
    {
        auto rpc_obj = std::make_unique<rpc::rtk::RtcmData>();

        rpc_obj->set_data(rtcm_data.data);

        return rpc_obj;
    }

    static mavsdk::Rtk::RtcmData translateFromRpcRtcmData(const rpc::rtk::RtcmData& rtcm_data)
    {
        mavsdk::Rtk::RtcmData obj;

        obj.data = rtcm_data.data();

        return obj;
    }

    static rpc::rtk::RtkResult::Result translateToRpcResult(const mavsdk::Rtk::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::Rtk::Result::Unknown:
                return rpc::rtk::RtkResult_Result_RESULT_UNKNOWN;
            case mavsdk::Rtk::Result::Success:
                return rpc::rtk::RtkResult_Result_RESULT_SUCCESS;
            case mavsdk::Rtk::Result::TooLong:
                return rpc::rtk::RtkResult_Result_RESULT_TOO_LONG;
            case mavsdk::Rtk::Result::NoSystem:
                return rpc::rtk::RtkResult_Result_RESULT_NO_SYSTEM;
            case mavsdk::Rtk::Result::ConnectionError:
                return rpc::rtk::RtkResult_Result_RESULT_CONNECTION_ERROR;
        }
    }

    static mavsdk::Rtk::Result translateFromRpcResult(const rpc::rtk::RtkResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::rtk::RtkResult_Result_RESULT_UNKNOWN:
                return mavsdk::Rtk::Result::Unknown;
            case rpc::rtk::RtkResult_Result_RESULT_SUCCESS:
                return mavsdk::Rtk::Result::Success;
            case rpc::rtk::RtkResult_Result_RESULT_TOO_LONG:
                return mavsdk::Rtk::Result::TooLong;
            case rpc::rtk::RtkResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::Rtk::Result::NoSystem;
            case rpc::rtk::RtkResult_Result_RESULT_CONNECTION_ERROR:
                return mavsdk::Rtk::Result::ConnectionError;
        }
    }

    grpc::Status SendRtcmData(
        grpc::ServerContext* /* context */,
        const rpc::rtk::SendRtcmDataRequest* request,
        rpc::rtk::SendRtcmDataResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Rtk::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SendRtcmData sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->send_rtcm_data(
            translateFromRpcRtcmData(request->rtcm_data()));

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