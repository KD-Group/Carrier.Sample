import time
import st
import os
import shutil

from .TCarrier.carrier import TCarrier
from .TCarrier.carrier.ttypes import TResult
from .TCarrier.carrier.ttypes import TSamplingConfig
from .TCarrier.carrier.ttypes import TReturnCode

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.transport.TTransport import TTransportException

from .result import Result


@st.singleton
class Sampler:
    def __init__(self):
        self.client: TCarrier.Client = None
        self.transport = None
        self.protocol = None
        self.execution_name = 'carrier_sample.exe'

    # must call start client before call other method except start server
    def start_client(self):
        if self.transport is None:
            self.transport = TSocket.TSocket("localhost", 9090)
            self.transport = TTransport.TBufferedTransport(self.transport)
        if self.protocol is None:
            self.protocol = TBinaryProtocol.TBinaryProtocol(self.transport)
        if self.client is None:
            self.client = TCarrier.Client(self.protocol)
        self.transport.open()

    def stop_client(self):
        if self.transport is not None:
            self.transport.close()

    def start_service(self, path: str):
        if self.check_service_running():
            return
        start_result = os.system('START /b ' + path)
        if start_result != 0:
            raise self.Error('Sampler Driver Service Start Failed, Check port 9090 is in use?')

    # Must call stop after program exit
    def stop_server(self):
        os.system(f'TASKKILL /F /IM "{self.execution_name}"')

    def check_service_running(self) -> bool:
        check_result = os.system(f'TASKLIST | findstr "{self.execution_name}"')
        if check_result != 0:
            return False
        return True

    def start_server(self):
        main_path = os.path.join(os.path.dirname(__file__), '..')

        # try to find exe file in different paths
        execution_path = self.execution_name
        if not os.path.exists(execution_path):
            execution_path = os.path.join(main_path, self.execution_name)
        if not os.path.exists(execution_path):
            execution_path = os.path.join(main_path, 'cpp_build', self.execution_name)
        if not os.path.exists(execution_path):
            execution_path = os.path.join(main_path, '..', '..', self.execution_name)
        if os.path.exists(execution_path):
            return self.start_service(os.path.abspath(execution_path))

        # try to find sample.exe in system path when release
        if shutil.which(self.execution_name):
            return self.start_service(shutil.which(self.execution_name))

        raise self.Error('Sample Driver Not Found')

    @property
    def is_measuring(self) -> bool:
        return self.client.is_measuring()

    def measure(self, number_of_waveforms: int, first_percent: float, second_percent: float) -> TReturnCode:
        config = TSamplingConfig()
        config.number_of_waveforms = number_of_waveforms
        config.first_percent = first_percent
        config.second_percent = second_percent
        return self.client.measure(config)

    def set_sampler(self, sampler_name: str) -> TReturnCode:
        return self.client.set_sampler(sampler_name)

    def get_sampler(self) -> str:
        return self.client.get_sampler()

    def set_sampler_value(self, key: str, value: float) -> TReturnCode:
        return self.client.set_sampler_value(key, value)

    def get_sampler_value(self, key: str) -> str:
        return self.client.get_sampler_value(key)

    def query(self) -> Result:
        thrift_result: TResult = self.client.to_query()
        result = Result()
        result.get_value_from_thrift(thrift_result)
        result.process()
        return result

    class Error(RuntimeError):
        pass


sampler = Sampler()
# Flowing is a simple example
# Must start server before client
# Every command returns a code whether the command is success except measuring && query
# WARNING: must call stop_server when program exit or crash

# try:
#     sampler.start_server()
#     sampler.start_client()
# except TTransportException as e:
#     print(e)
# except Sampler.Error as e:
#     print(e)
# set_sampler_result: TReturnCode = sampler.set_sampler("mock_sampler")
# measure_result: TReturnCode = sampler.measure(4, 0.147, 0.4)
# while sampler.is_measuring:
#     time.sleep(0.1)
# start_time = time.time()
# result: Result = sampler.query()
# print(f"query cost time {time.time() - start_time}")
# if result.error:
#     print("Measure Failed")
# else:
#     print(f"Measure Success, tau value is {result.tau}")
