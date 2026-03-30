# spdlog

## 用法

```cpp
// 多线程日志
auto logger = spdlog::stdout_color_mt("console"); // ✅ mt

// 设置输出模式
logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%^%l%$] [%s:%#] %v");
```

## spdlog pattern

https://github.com/gabime/spdlog/wiki/Custom-formatting
