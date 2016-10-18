package bank

type withdraw struct {
	amount int
	result chan<- bool
}

var deposits = make(chan int)
var balances = make(chan int)
var withdraws = make(chan withdraw)

func Deposit(amount int) { deposits <- amount }
func Balance() int       { return <-balances }

func teller() {
	balance := 0
	for {
		select {
		case amount := <-deposits:
			balance += amount
		case wd := <-withdraws:
			if wd.amount > balance {
				wd.result <- false
				break
			}
			balance -= wd.amount
			wd.result <- true
		case balances <- balance:
		}
	}
}

func init() {
	go teller()
}

func Withdraw(amount int) bool {
	result := make(chan bool)
	withdraws <- withdraw{amount, result}
	return <-result
}
