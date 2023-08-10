export SARSA_DIR=$(cd $(dirname ${BASH_SOURCE:-$0}) && pwd -P)

export SARSA_SRC=$SARSA_DIR/src
export SARSA_TUTORIALS=$SARSA_DIR/tutorials
export SARSA_RUN=$SARSA_DIR/run
export SARSA_BIN=$SARSA_DIR/bin
# export SARSA_SOLVERS=$SARSA_APP/solvers
# export SARSA_ETC=$SARSA_DIR/etc
# export SARSA_APP=$SARSA_DIR/applications


alias src='cd $SARSA_SRC'
alias tut='cd $SARSA_TUTORIALS'
alias run='cd $SARSA_RUN'
alias sarsa='$SARSA_BIN/sarsa'
# alias lib='cd $SARSA_LIBBIN'
# alias app='cd $SARSA_APP'
# alias sol='cd $SARSA_SOLVERS'
# alias util='cd $SARSA_UTILITIES'
