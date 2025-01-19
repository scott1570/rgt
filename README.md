# POS Demo system

디자인 : clear architecture

사용기술 : design patterining/JSON/HTTP/THREAD/TCPIP/MFC UI

프로젝트 :

1. POSService : POS 통신을 담당하며 json parsing logic 구현.
   1) 시간이 부족하여 design pattern 적용하지 못했습니다.
   2) service handle이 권한 문제로 cresh handling(restart) 를 코드로만 구현되었습니다.
   3) debug 및 데모는 console 모드로 동작시켰으며 service 상태에서도 돌아갑니다.
   4) IPC는 POSMain (UI) 와 TCP 통신을 사용하였습니다.
   5) test의 경우 postman에서 하기와 같이 json을 입력하여도 테스트 가능합니다.
      
{
    "order": [
        {
            "menu": "dog",
            "amount": "3"
        },
        {
            "menu": "salt",
            "amount": "2"
        }],
    "table": "1",
    "status": "1"
}

2. POSMain : Clear Architecture를 흉내를 내었습니다.
   1) Entity : 자료구조 저장/업데이트
   2) UseCases : order 만 구현됨, cancel 등 구현이 안되었습니다.
   3) DummyPosClient or Postman 에 의해 들어오는 Json을 PosService 를 통해 처리된 데이터를 받아 자체 자료구조에 저장하여 새로운 주문,상태 업데이트에 적용하였습니다.
   4) 실행파일이 있는 디렉터리에 config.json 이 필요하며 내용은 접속할 Service 의 ip,port 입니다.
3. DummyPosClient : Input Json 을 랜덤하게 생성하여, POSService로 전송하는 역할을 수행합니다.


   실행 순서는 각 프로젝트를 Visual studio에서 로드후,
   POSService 실행
   POSMain 실행
   DummyPOSClient 실행후, start 버튼 클릭


* 총평 : 2번 UI의 경우 전문적이지 않은 ,UI지식으로 구현하여 많이 부족해 보이며, Service등도 권한문제를 다루는데 부족한 부분이 있습니다.
  TCP/Thread 구조나, 자료구조는 비교적 간결하게 작성되었습니다.


  감사합니다.




