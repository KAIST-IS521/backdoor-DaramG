# Test 

`test.mini` contains test cases of all instructions which check that my VM works correctly.

```c
void test(){
  uint8_t* buf = malloc(8192);

  // puts, store, puti, move
  puts("Index :");
  
  // gets
  gets(buf);

  //load, add
  uint8_t tmp = buf[0]+ buf[1];

  //sub
  buf[0] -=buf[1];

  // ite, eq
  if(tmp== 0x41)puts("1");
  else{

  // ite,gt
    if(tmp > 0x41)puts("2");
    else{

  //ite,ge
      if(tmp >= 0x20)puts("3");
      else puts("4");

    }
  }
  // jump
  goto END:

END:
  // halt
  exit(0);

}
```
