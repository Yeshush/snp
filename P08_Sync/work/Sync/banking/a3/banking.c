//******************************************************************************
// Course:  BSy
// File:    banking.c
// Author:  M. Thaler, ZHAW
// Purpose: locking mechanisms
// Version: v.fs24
//******************************************************************************

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "banking.h"

//******************************************************************************

typedef struct account_struct_ {
    long int balance;
    pthread_mutex_t acntLock;
} Account;

typedef struct branch_struct {
    Account *accounts;
    pthread_mutex_t branchLock; 
} Branch;

//******************************************************************************

static Branch *bank;
static int nBranches, nAccounts;

//******************************************************************************
// banking functions

void makeBank(int num_branches, int num_accounts) {
    nBranches = num_branches;
    nAccounts = num_accounts;
    bank = (Branch *)malloc(nBranches * sizeof(Branch));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    //pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);

    for (int  i = 0; i < nBranches; i++) {
        bank[i].accounts = (Account *)malloc(nAccounts * sizeof(Account));
        for (int j = 0; j < nAccounts; j++) {
            pthread_mutex_init(&bank[i].accounts[j].acntLock, NULL);
            bank[i].accounts[j].balance = 0;
        }
    }
}

void deletebank(void) {
    for (int i = 0; i < nBranches; i++)
        free(bank[i].accounts);
    free(bank);
    nBranches = nAccounts = 0;
}

long int withdraw(int branchNr, int accountNr, long int value) {
    int rv, tmp;
    rv = 0;
    tmp = bank[branchNr].accounts[accountNr].balance - value;
    if (tmp >= 0) {
        bank[branchNr].accounts[accountNr].balance = tmp;
        rv = value;
    };
    return rv;   
}

void deposit(int branchNr, int accountNr, long int value) {
    bank[branchNr].accounts[accountNr].balance += value;
}

void transfer(int fromB, int toB, int accountNr, long int value) {
    // Determine the order of locking to avoid deadlocks
    int firstB, secondB;
    if (fromB < toB) {
        firstB = fromB;
        secondB = toB;
    } else {
        firstB = toB;
        secondB = fromB;
    }

    // Lock the branches in order
    pthread_mutex_lock(&bank[firstB].branchLock);
    if (firstB != secondB) {
        pthread_mutex_lock(&bank[secondB].branchLock);
    }

    // Lock the accounts
    pthread_mutex_lock(&bank[fromB].accounts[accountNr].acntLock);
    if (fromB != toB) {
        pthread_mutex_lock(&bank[toB].accounts[accountNr].acntLock);
    }

    // Perform the transfer
    int money = withdraw(fromB, accountNr, value);
    deposit(toB, accountNr, money);

    // Unlock the accounts
    pthread_mutex_unlock(&bank[fromB].accounts[accountNr].acntLock);
    if (fromB != toB) {
        pthread_mutex_unlock(&bank[toB].accounts[accountNr].acntLock);
    }

    // Unlock the branches
    pthread_mutex_unlock(&bank[firstB].branchLock);
    if (firstB != secondB) {
        pthread_mutex_unlock(&bank[secondB].branchLock);
    }
}

void checkAssets(void) {
    static long assets = 0;
    long int sum = 0;
    for (int i = 0; i < nBranches; i++) {
        for (int j = 0; j < nAccounts; j++) {
            sum += (long int)bank[i].accounts[j].balance;
        }
    }
    if (assets == 0) {
        assets = sum;
        printf("Balance of accounts is: %ld\n", sum);
    }
    else {
        if (sum != assets) {
            printf("Balance of accounts is: %ld ... not correct\n", sum);
        }
        else
            printf("Balance of accounts is: %ld ... correct\n", assets);
    }
}

int checkIBC(void) {
    static long ibcError = 0;
    long sum = 0;

    for (int i = 0; i < nBranches; i++) {
        pthread_mutex_lock(&bank[i].branchLock);
        for (int j = 0; j < nAccounts; j++) {
            pthread_mutex_lock(&bank[i].accounts[j].acntLock);
        }
    }
    for (int i = 0; i < nBranches; i++) {
        for (int j = 0; j < nAccounts; j++) {        
            sum += (long)bank[i].accounts[j].balance;
        }
    }
    for (int i = nBranches - 1; i >= 0; i--) {
        pthread_mutex_unlock(&bank[i].branchLock);
        for (int j = 0; j < nAccounts; j++) {
            pthread_mutex_unlock(&bank[i].accounts[j].acntLock);
        }
    }
    if (ibcError == 0) ibcError = sum;
    return (ibcError != sum);
}
//******************************************************************************

