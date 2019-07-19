# linux 命名空间（namespace ）

目前，Linux实现了六种不同类型的命名空间。每个命名空间的目的是将一个特定的全局系统资源包装在一个抽象中，使得它在命名空间内的进程看来它们拥有自己独立的全局资源实例。命名空间的总体目标之一是支持容器的实现，是轻量级虚拟化（以及其他用途）的工具，它为一组进程提供了一个错觉，即它们是系统上唯一的进程。

## Mount namespace

## UTS namespace

## IPC namespace

## PID namespace

## Network namespace

## User namespace

https://lwn.net/Articles/531114/