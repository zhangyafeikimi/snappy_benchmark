# benchmark

## AMD EPYC 7K62 48-Core Processor

### GCC 8.5.0

```plain
Benchmarking with file "testdata/geo.protodata".

Compressing 118588 bytes.
1.0.4=9.551 ops/ms
1.1.3=9.950 ops/ms
1.1.10=20.568 ops/ms
1.2.1(STLStringResizeUninitialized)=16.815 ops/ms
1.2.2(STLStringResizeUninitialized)=17.127 ops/ms

Uncompressing 23242 bytes.
1.0.4=27.158 ops/ms
1.1.3=26.037 ops/ms
1.1.10=51.793 ops/ms
1.2.1(STLStringResizeUninitialized)=18.000 ops/ms
1.2.2(STLStringResizeUninitialized)=18.519 ops/ms
```
