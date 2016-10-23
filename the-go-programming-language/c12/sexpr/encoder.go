package sexpr

import (
	"bytes"
	"fmt"
	"reflect"
)

func Marshal(v interface{}) ([]byte, error) {
	var buf bytes.Buffer
	if err := encode(&buf, reflect.ValueOf(v)); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

func encode(buf *bytes.Buffer, v reflect.Value) error {
	switch v.Kind() {
	case reflect.Invalid:
		buf.WriteString("nil")

	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		fmt.Fprintf(buf, "%d", v.Int())

	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		fmt.Fprintf(buf, "%d", v.Uint())

	case reflect.String:
		fmt.Fprintf(buf, "%q", v.String())

	case reflect.Ptr:
		return encode(buf, v.Elem())

	case reflect.Array, reflect.Slice: // (value ...)
		buf.WriteRune('(')
		for i := 0; i < v.Len(); i++ {
			if i > 0 {
				buf.WriteRune(' ')
			}
			if err := encode(buf, v.Index(i)); err != nil {
				return err
			}
		}
		buf.WriteRune(')')

	case reflect.Struct: // ((name value) ...)
		buf.WriteRune('(')
		for i := 0; i < v.NumField(); i++ {
			if i > 0 {
				buf.WriteRune(' ')
			}
			fmt.Fprintf(buf, "(%s ", v.Type().Field(i).Name)
			if err := encode(buf, v.Field(i)); err != nil {
				return err
			}
			buf.WriteRune(')')
		}
		buf.WriteRune(')')

	case reflect.Map: // ((key value) ...)
		buf.WriteRune('(')
		for i, key := range v.MapKeys() {
			if i > 0 {
				buf.WriteRune(' ')
			}
			buf.WriteRune('(')
			if err := encode(buf, key); err != nil {
				return err
			}
			buf.WriteRune(' ')
			if err := encode(buf, v.MapIndex(key)); err != nil {
				return err
			}
			buf.WriteRune(')')
		}
		buf.WriteRune(')')

	default: // float, complex, bool, chan, func, interface
		return fmt.Errorf("unsupported type %s", v.Type())
	}
	return nil
}
