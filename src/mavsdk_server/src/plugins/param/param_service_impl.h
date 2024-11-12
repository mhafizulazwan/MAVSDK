// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/param/param.proto)

#include "param/param.grpc.pb.h"
#include "plugins/param/param.h"

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

template<typename Param = Param, typename LazyPlugin = LazyPlugin<Param>>

class ParamServiceImpl final : public rpc::param::ParamService::Service {
public:
    ParamServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}

    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::Param::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_param_result = new rpc::param::ParamResult();
        rpc_param_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_param_result->set_result_str(ss.str());

        response->set_allocated_param_result(rpc_param_result);
    }

    static rpc::param::ProtocolVersion
    translateToRpcProtocolVersion(const mavsdk::Param::ProtocolVersion& protocol_version)
    {
        switch (protocol_version) {
            default:
                LogErr() << "Unknown protocol_version enum value: "
                         << static_cast<int>(protocol_version);
            // FALLTHROUGH
            case mavsdk::Param::ProtocolVersion::V1:
                return rpc::param::PROTOCOL_VERSION_V1;
            case mavsdk::Param::ProtocolVersion::Ext:
                return rpc::param::PROTOCOL_VERSION_EXT;
        }
    }

    static mavsdk::Param::ProtocolVersion
    translateFromRpcProtocolVersion(const rpc::param::ProtocolVersion protocol_version)
    {
        switch (protocol_version) {
            default:
                LogErr() << "Unknown protocol_version enum value: "
                         << static_cast<int>(protocol_version);
            // FALLTHROUGH
            case rpc::param::PROTOCOL_VERSION_V1:
                return mavsdk::Param::ProtocolVersion::V1;
            case rpc::param::PROTOCOL_VERSION_EXT:
                return mavsdk::Param::ProtocolVersion::Ext;
        }
    }

    static std::unique_ptr<rpc::param::IntParam>
    translateToRpcIntParam(const mavsdk::Param::IntParam& int_param)
    {
        auto rpc_obj = std::make_unique<rpc::param::IntParam>();

        rpc_obj->set_name(int_param.name);

        rpc_obj->set_value(int_param.value);

        return rpc_obj;
    }

    static mavsdk::Param::IntParam translateFromRpcIntParam(const rpc::param::IntParam& int_param)
    {
        mavsdk::Param::IntParam obj;

        obj.name = int_param.name();

        obj.value = int_param.value();

        return obj;
    }

    static std::unique_ptr<rpc::param::FloatParam>
    translateToRpcFloatParam(const mavsdk::Param::FloatParam& float_param)
    {
        auto rpc_obj = std::make_unique<rpc::param::FloatParam>();

        rpc_obj->set_name(float_param.name);

        rpc_obj->set_value(float_param.value);

        return rpc_obj;
    }

    static mavsdk::Param::FloatParam
    translateFromRpcFloatParam(const rpc::param::FloatParam& float_param)
    {
        mavsdk::Param::FloatParam obj;

        obj.name = float_param.name();

        obj.value = float_param.value();

        return obj;
    }

    static std::unique_ptr<rpc::param::CustomParam>
    translateToRpcCustomParam(const mavsdk::Param::CustomParam& custom_param)
    {
        auto rpc_obj = std::make_unique<rpc::param::CustomParam>();

        rpc_obj->set_name(custom_param.name);

        rpc_obj->set_value(custom_param.value);

        return rpc_obj;
    }

    static mavsdk::Param::CustomParam
    translateFromRpcCustomParam(const rpc::param::CustomParam& custom_param)
    {
        mavsdk::Param::CustomParam obj;

        obj.name = custom_param.name();

        obj.value = custom_param.value();

        return obj;
    }

    static std::unique_ptr<rpc::param::AllParams>
    translateToRpcAllParams(const mavsdk::Param::AllParams& all_params)
    {
        auto rpc_obj = std::make_unique<rpc::param::AllParams>();

        for (const auto& elem : all_params.int_params) {
            auto* ptr = rpc_obj->add_int_params();
            ptr->CopyFrom(*translateToRpcIntParam(elem).release());
        }

        for (const auto& elem : all_params.float_params) {
            auto* ptr = rpc_obj->add_float_params();
            ptr->CopyFrom(*translateToRpcFloatParam(elem).release());
        }

        for (const auto& elem : all_params.custom_params) {
            auto* ptr = rpc_obj->add_custom_params();
            ptr->CopyFrom(*translateToRpcCustomParam(elem).release());
        }

        return rpc_obj;
    }

    static mavsdk::Param::AllParams
    translateFromRpcAllParams(const rpc::param::AllParams& all_params)
    {
        mavsdk::Param::AllParams obj;

        for (const auto& elem : all_params.int_params()) {
            obj.int_params.push_back(
                translateFromRpcIntParam(static_cast<mavsdk::rpc::param::IntParam>(elem)));
        }

        for (const auto& elem : all_params.float_params()) {
            obj.float_params.push_back(
                translateFromRpcFloatParam(static_cast<mavsdk::rpc::param::FloatParam>(elem)));
        }

        for (const auto& elem : all_params.custom_params()) {
            obj.custom_params.push_back(
                translateFromRpcCustomParam(static_cast<mavsdk::rpc::param::CustomParam>(elem)));
        }

        return obj;
    }

    static rpc::param::ParamResult::Result translateToRpcResult(const mavsdk::Param::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::Param::Result::Unknown:
                return rpc::param::ParamResult_Result_RESULT_UNKNOWN;
            case mavsdk::Param::Result::Success:
                return rpc::param::ParamResult_Result_RESULT_SUCCESS;
            case mavsdk::Param::Result::Timeout:
                return rpc::param::ParamResult_Result_RESULT_TIMEOUT;
            case mavsdk::Param::Result::ConnectionError:
                return rpc::param::ParamResult_Result_RESULT_CONNECTION_ERROR;
            case mavsdk::Param::Result::WrongType:
                return rpc::param::ParamResult_Result_RESULT_WRONG_TYPE;
            case mavsdk::Param::Result::ParamNameTooLong:
                return rpc::param::ParamResult_Result_RESULT_PARAM_NAME_TOO_LONG;
            case mavsdk::Param::Result::NoSystem:
                return rpc::param::ParamResult_Result_RESULT_NO_SYSTEM;
            case mavsdk::Param::Result::ParamValueTooLong:
                return rpc::param::ParamResult_Result_RESULT_PARAM_VALUE_TOO_LONG;
            case mavsdk::Param::Result::Failed:
                return rpc::param::ParamResult_Result_RESULT_FAILED;
        }
    }

    static mavsdk::Param::Result
    translateFromRpcResult(const rpc::param::ParamResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::param::ParamResult_Result_RESULT_UNKNOWN:
                return mavsdk::Param::Result::Unknown;
            case rpc::param::ParamResult_Result_RESULT_SUCCESS:
                return mavsdk::Param::Result::Success;
            case rpc::param::ParamResult_Result_RESULT_TIMEOUT:
                return mavsdk::Param::Result::Timeout;
            case rpc::param::ParamResult_Result_RESULT_CONNECTION_ERROR:
                return mavsdk::Param::Result::ConnectionError;
            case rpc::param::ParamResult_Result_RESULT_WRONG_TYPE:
                return mavsdk::Param::Result::WrongType;
            case rpc::param::ParamResult_Result_RESULT_PARAM_NAME_TOO_LONG:
                return mavsdk::Param::Result::ParamNameTooLong;
            case rpc::param::ParamResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::Param::Result::NoSystem;
            case rpc::param::ParamResult_Result_RESULT_PARAM_VALUE_TOO_LONG:
                return mavsdk::Param::Result::ParamValueTooLong;
            case rpc::param::ParamResult_Result_RESULT_FAILED:
                return mavsdk::Param::Result::Failed;
        }
    }

    grpc::Status GetParamInt(
        grpc::ServerContext* /* context */,
        const rpc::param::GetParamIntRequest* request,
        rpc::param::GetParamIntResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Param::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "GetParamInt sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_param_int(request->name());

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_value(result.second);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetParamInt(
        grpc::ServerContext* /* context */,
        const rpc::param::SetParamIntRequest* request,
        rpc::param::SetParamIntResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Param::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetParamInt sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->set_param_int(request->name(), request->value());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status GetParamFloat(
        grpc::ServerContext* /* context */,
        const rpc::param::GetParamFloatRequest* request,
        rpc::param::GetParamFloatResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Param::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "GetParamFloat sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_param_float(request->name());

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_value(result.second);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetParamFloat(
        grpc::ServerContext* /* context */,
        const rpc::param::SetParamFloatRequest* request,
        rpc::param::SetParamFloatResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Param::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetParamFloat sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result =
            _lazy_plugin.maybe_plugin()->set_param_float(request->name(), request->value());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status GetParamCustom(
        grpc::ServerContext* /* context */,
        const rpc::param::GetParamCustomRequest* request,
        rpc::param::GetParamCustomResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Param::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "GetParamCustom sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_param_custom(request->name());

        if (response != nullptr) {
            fillResponseWithResult(response, result.first);

            response->set_value(result.second);
        }

        return grpc::Status::OK;
    }

    grpc::Status SetParamCustom(
        grpc::ServerContext* /* context */,
        const rpc::param::SetParamCustomRequest* request,
        rpc::param::SetParamCustomResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Param::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SetParamCustom sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result =
            _lazy_plugin.maybe_plugin()->set_param_custom(request->name(), request->value());

        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }

        return grpc::Status::OK;
    }

    grpc::Status GetAllParams(
        grpc::ServerContext* /* context */,
        const rpc::param::GetAllParamsRequest* /* request */,
        rpc::param::GetAllParamsResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->get_all_params();

        if (response != nullptr) {
            response->set_allocated_params(translateToRpcAllParams(result).release());
        }

        return grpc::Status::OK;
    }

    grpc::Status SelectComponent(
        grpc::ServerContext* /* context */,
        const rpc::param::SelectComponentRequest* request,
        rpc::param::SelectComponentResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            if (response != nullptr) {
                auto result = mavsdk::Param::Result::NoSystem;
                fillResponseWithResult(response, result);
            }

            return grpc::Status::OK;
        }

        if (request == nullptr) {
            LogWarn() << "SelectComponent sent with a null request! Ignoring...";
            return grpc::Status::OK;
        }

        auto result = _lazy_plugin.maybe_plugin()->select_component(
            request->component_id(), translateFromRpcProtocolVersion(request->protocol_version()));

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