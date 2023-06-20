#!/bin/bash

function promedio() {
  local prom=0
  for i in $(seq 20); do
    local t=$(./cmake-build-debug/ej1benchmark "$1" < "$2")
    prom=$(echo "$prom + $t" | bc)
  done
  prom=$(echo "$prom * 0.2" | bc)
  echo $prom
}

DIJKSTRSA_RALO=0;
DIJKSTRSA_DENSO=1;
DIJKSTRSA_FIB=2;
BELLMAN_FORD=3;

promedio "$DIJKSTRSA_RALO" "$1"
promedio "$DIJKSTRSA_DENSO" "$1"
promedio "$DIJKSTRSA_FIB" "$1"
promedio "$BELLMAN_FORD" "$1"
