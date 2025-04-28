# LANG-SHUNG-JWAK-ASM

[랭슝좍](https://github.com/nabibear33/Lang-shung-jwak)의 어셈블리어 구현체입니다. 어셈블러는 [FASM](https://flatassembler.net/)을 사용하였습니다. 언어에 대한 설명은 원본 레포의 README.md를 참고해 주세요.

코드는 윈도우를 기준으로 작성되었습니다.

## 빌드

빌드를 하기 위해선 fasm가 설치되어 있어야 합니다.

### Jwak 빌드

```
fasm main.asm jwak.exe
```

### test 빌드

디버깅을 위해선 x64dbg같은 디버거가 필요합니다.

```
fasm test/파일이름.asm test_파일이름.exe
```
