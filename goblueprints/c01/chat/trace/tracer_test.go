package trace

import (
	"bytes"
	"testing"
)

func TestNew(t *testing.T) {
	var buf bytes.Buffer
	tracer := New(&buf)
	tracer.Trace("Hello, trace package")
	if buf.String() != "Hello, trace package\n" {
		t.Errorf("wrong message: %q", buf.String())
	}
}

func TestTraceToNil(t *testing.T) {
	var tracer Tracer
	tracer.Trace("This message should not be traced")
}
