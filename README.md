# API_server

WinSock2 / API socket을 이용하여 tcp서버 만들기

1. socket 생성

2. bind 
API가 해당 소켓이 지정된 포트 번호를 사용할 것이라는 것을 운영체제에 요청하는 것.
운영체제가 소켓과 포트 번호를 bind, 즉 결합
지정된 포트 번호를 다른 소켓이 사용한다면 error리턴
서버 소켓은 고정된 포트 번호를 사용하고, 그 포트로 client의 연결 요청을 받음.

3. listen
client의 요청(connect)을 확인하며 대기상태에 머무름.
연결 요청이 수신 되었는지 아닌지만 판단함.
연결을 완료하기 위해서는 accpet 함수를 호출해야 함

4. accpet
연결 요청(connect)를 받아 소켓간 연결을 함
앞에서의 연결을 받아들이기 위한 서버 소켓의 일은 끝남
실제 데이터의 send,recv는 accpet 함수 내부에서 생성된 소켓을 통해 처리

5. close
