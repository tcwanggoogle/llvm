//===- RecordPrinter.cpp - FDR Record Printer -----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "llvm/XRay/RecordPrinter.h"

#include "llvm/Support/FormatVariadic.h"

namespace llvm {
namespace xray {

Error RecordPrinter::visit(BufferExtents &R) {
  OS << formatv("<Buffer: size = {0} bytes>", R.size()) << Delim;
  return Error::success();
}

Error RecordPrinter::visit(WallclockRecord &R) {
  OS << formatv("<Wall Time: seconds = {0}.{1,0+6}>", R.seconds(), R.nanos())
     << Delim;
  return Error::success();
}

Error RecordPrinter::visit(NewCPUIDRecord &R) {
  OS << formatv("<CPU: id = {0}, tsc = {1}>", R.cpuid(), R.tsc()) << Delim;
  return Error::success();
}

Error RecordPrinter::visit(TSCWrapRecord &R) {
  OS << formatv("<TSC Wrap: base = {0}>", R.tsc()) << Delim;
  return Error::success();
}

Error RecordPrinter::visit(CustomEventRecord &R) {
  OS << formatv("<Custom Event: tsc = {0}, size = {1}, data = '{2}'>", R.tsc(),
                R.size(), R.data())
     << Delim;
  return Error::success();
}

Error RecordPrinter::visit(CallArgRecord &R) {
  OS << formatv("<Call Argument: data = {0} (hex = {0:x})>", R.arg()) << Delim;
  return Error::success();
}

Error RecordPrinter::visit(PIDRecord &R) {
  OS << formatv("<PID: {0}>", R.pid()) << Delim;
  return Error::success();
}

Error RecordPrinter::visit(NewBufferRecord &R) {
  OS << formatv("<Thread ID: {0}>", R.tid()) << Delim;
  return Error::success();
}

Error RecordPrinter::visit(EndBufferRecord &R) {
  OS << "<End of Buffer>" << Delim;
  return Error::success();
}

Error RecordPrinter::visit(FunctionRecord &R) {
  // FIXME: Support symbolization here?
  switch (R.recordType()) {
  case RecordTypes::ENTER:
    OS << formatv("<Function Enter: #{0} delta = +{0}>", R.functionId(),
                  R.delta());
    break;
  case RecordTypes::ENTER_ARG:
    OS << formatv("<Function Enter With Arg: #{0} delta = +{0}>",
                  R.functionId(), R.delta());
    break;
  case RecordTypes::EXIT:
    OS << formatv("<Function Exit: #{0} delta = +{0}>", R.functionId(),
                  R.delta());
    break;
  case RecordTypes::TAIL_EXIT:
    OS << formatv("<Function Tail Exit: #{0} delta = +{0}>", R.functionId(),
                  R.delta());
    break;
  }
  OS << Delim;
  return Error::success();
}

} // namespace xray
} // namespace llvm
