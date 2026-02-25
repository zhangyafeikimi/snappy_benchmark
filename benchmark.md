# benchmark

## AMD EPYC 7K62 48-Core Processor

### GCC 8.5.0

```plain
Benchmarking with file "testdata/geo.protodata".

Compressing 118588 bytes.
1.0.4=9.276 ops/ms
1.1.3=10.018 ops/ms
1.1.10=14.911 ops/ms
1.2.1(STLStringResizeUninitialized)=13.410 ops/ms
1.2.2(STLStringResizeUninitialized)=13.685 ops/ms

Uncompressing 23140 bytes.
1.0.4=24.925 ops/ms
1.1.3=24.655 ops/ms
1.1.10=45.862 ops/ms
1.2.1(STLStringResizeUninitialized)=44.910 ops/ms
1.2.2(STLStringResizeUninitialized)=47.761 ops/ms
```
