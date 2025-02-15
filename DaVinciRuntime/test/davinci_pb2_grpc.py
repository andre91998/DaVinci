# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc
import warnings

import davinci_pb2 as davinci__pb2

GRPC_GENERATED_VERSION = '1.70.0'
GRPC_VERSION = grpc.__version__
_version_not_supported = False

try:
    from grpc._utilities import first_version_is_lower
    _version_not_supported = first_version_is_lower(GRPC_VERSION, GRPC_GENERATED_VERSION)
except ImportError:
    _version_not_supported = True

if _version_not_supported:
    raise RuntimeError(
        f'The grpc package installed is at version {GRPC_VERSION},'
        + f' but the generated code in davinci_pb2_grpc.py depends on'
        + f' grpcio>={GRPC_GENERATED_VERSION}.'
        + f' Please upgrade your grpc module to grpcio>={GRPC_GENERATED_VERSION}'
        + f' or downgrade your generated code using grpcio-tools<={GRPC_VERSION}.'
    )


class DaVinciServiceStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.GetDimmerData = channel.unary_unary(
                '/daVinciRPC.DaVinciService/GetDimmerData',
                request_serializer=davinci__pb2.Empty.SerializeToString,
                response_deserializer=davinci__pb2.RPC_DimmerDataArray.FromString,
                _registered_method=True)
        self.GetPlugData = channel.unary_unary(
                '/daVinciRPC.DaVinciService/GetPlugData',
                request_serializer=davinci__pb2.Empty.SerializeToString,
                response_deserializer=davinci__pb2.RPC_PlugDataArray.FromString,
                _registered_method=True)
        self.GetTemperatureData = channel.unary_unary(
                '/daVinciRPC.DaVinciService/GetTemperatureData',
                request_serializer=davinci__pb2.Empty.SerializeToString,
                response_deserializer=davinci__pb2.RPC_TemperatureDataArray.FromString,
                _registered_method=True)


class DaVinciServiceServicer(object):
    """Missing associated documentation comment in .proto file."""

    def GetDimmerData(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def GetPlugData(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def GetTemperatureData(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_DaVinciServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'GetDimmerData': grpc.unary_unary_rpc_method_handler(
                    servicer.GetDimmerData,
                    request_deserializer=davinci__pb2.Empty.FromString,
                    response_serializer=davinci__pb2.RPC_DimmerDataArray.SerializeToString,
            ),
            'GetPlugData': grpc.unary_unary_rpc_method_handler(
                    servicer.GetPlugData,
                    request_deserializer=davinci__pb2.Empty.FromString,
                    response_serializer=davinci__pb2.RPC_PlugDataArray.SerializeToString,
            ),
            'GetTemperatureData': grpc.unary_unary_rpc_method_handler(
                    servicer.GetTemperatureData,
                    request_deserializer=davinci__pb2.Empty.FromString,
                    response_serializer=davinci__pb2.RPC_TemperatureDataArray.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'daVinciRPC.DaVinciService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('daVinciRPC.DaVinciService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class DaVinciService(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def GetDimmerData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/daVinciRPC.DaVinciService/GetDimmerData',
            davinci__pb2.Empty.SerializeToString,
            davinci__pb2.RPC_DimmerDataArray.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def GetPlugData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/daVinciRPC.DaVinciService/GetPlugData',
            davinci__pb2.Empty.SerializeToString,
            davinci__pb2.RPC_PlugDataArray.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def GetTemperatureData(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/daVinciRPC.DaVinciService/GetTemperatureData',
            davinci__pb2.Empty.SerializeToString,
            davinci__pb2.RPC_TemperatureDataArray.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
