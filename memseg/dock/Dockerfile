FROM ubuntu:12.04

# 이전에 존재하던 source 리스트 삭제
RUN rm /etc/apt/source.list
# 현재 환경에 있는 source 리스트 추가
COPY source.list /etc/apt

# 이후 수행할 작업들
# apt-get 업데이트 하기
# apt로부터 zsh 다운로드하기
RUN apt-get update
RUN apt-get install zsh

# 기본 명령으로는 bash 시작
CMD ["bash"]

