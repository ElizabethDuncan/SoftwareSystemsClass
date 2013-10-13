# bathroom
empty = Semaphore(1)
maleSwitch = Lightswitch()
femaleSwitch = Lightswitch()
maleMultiplex = Semaphore(3)
femaleMultiplex = Semaphore(3)
turnstile = Semaphore(1)

## Thread
# Females
femaleSwitch.lock(empty)
femaleMultiplex.wait()
# bathroom code here
femaleMultiplex.signal()
femaleSwitch.unlock(empty)

## Thread
# Males
turnstile.wait()
maleSwitch.lock(empty)
turnstile.signal()
maleMultiplex.wait()
# bathroom code here
maleMultiplex.signal()
maleSwitch.unlock (empty)
