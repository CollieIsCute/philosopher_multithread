# philosopher_multithread

## 操作方式

- 使用 makefile 指令編譯。
  - `make all`: 編譯並產生執行檔 `main.elf` 。
  - `make format`: 排版。
  - `make clean`: 清除不需要的檔案。
- 可用 `make format` 排版，並且用 `make clean all` 來編譯並獲得執行檔。獲得執行檔後，執行該檔案，即可按照作業範例輸入獲得輸出。
- 第0個參數是執行檔本身，第一個參數是m, 第二個參數是n, 使用方式完全與規格書相同，m是選擇要測試的演算法，n則是哲學家的執行緒數量。

## 設計理念

- 規格書裡面有說的所有功能皆有實作。目標是盡可能寫 c++, 少寫 c code. 且學習使用 clean code 和 OOP 概念，讓程式碼盡量簡潔且重用性高。注意：此份作業有實做 deadlock detection. 作法是設個 DeadlockPhilosopher class 的 static counter, 去計算有多少個 philosopher(亦即thread)是擁有 chopstick lock 的，當 counter == chopstick 的 size 時，即代表每個 philosopher 都必只拿一個 chopstick, 並開始等待，也就是進入 deadlock. 此時會 throw 一個 runtime_exception 出來，詳情請見 DeadlockPhilosopher class 的實做。

## 特殊 library

- 無。此作業只有用到 c++ 的一般 library, 並無額外使用其他 library.
