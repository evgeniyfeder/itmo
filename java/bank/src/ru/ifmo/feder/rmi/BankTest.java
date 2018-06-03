package ru.ifmo.feder.rmi;

import org.junit.Test;

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.*;

import static junit.framework.TestCase.assertNotNull;
import static junit.framework.TestCase.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class BankTest {

    private static Bank bank;

    private static final int PEOPLE = 100;
    private static final int ACCOUNTS = 1000;

    @org.junit.BeforeClass
    public static void beforeClass() throws Exception {
        Naming.rebind("//localhost/bank", new RemoteBank(8888));
        bank = (Bank) Naming.lookup("//localhost/bank");

        System.out.println("Bank created");
    }

    @Test
    public void getPerson() throws RemoteException {
        assertNull(bank.getLocalPerson("" + (-PEOPLE - 1)));
        assertNull(bank.getRemotePerson("" + (-PEOPLE - 1)));
        for (int i = 0; i < PEOPLE; ++i) {
            bank.createPerson("getPerson" + i, "", "getPerson" + i);
            Person remotePerson = bank.getRemotePerson("getPerson" + i);
            assertEquals("getPerson" + i, remotePerson.getName());
            assertEquals("", remotePerson.getSurname());
            assertEquals("getPerson" + i, remotePerson.getPasportId());

            Person localPerson = bank.getLocalPerson("getPerson" + i);
            assertEquals("getPerson" + i, localPerson.getName());
            assertEquals("", localPerson.getSurname());
            assertEquals("getPerson" + i, localPerson.getPasportId());

        }
    }

    @Test
    public void getAccountIds() throws RemoteException {
        Random random = new Random();
        for (int i = 0; i < PEOPLE; ++i) {
            assertTrue(bank.createPerson("getAccountsIds", "" + i, "getAccountsIds" + i));

            int needOperations = random.nextInt(PEOPLE), doneNum = 0;
            Person remote = bank.getRemotePerson("getAccountsIds" + i);
            for (int j = 0; j < needOperations; j++) {
                if (bank.createAccount(remote, "" + random.nextInt()))
                    doneNum++;
            }
            Set<String> ids = bank.getPersonAccounts(remote);
            assertNotNull(ids);
            assertEquals(doneNum, ids.size());
        }
    }

    @Test
    public void checkAndCreatePerson() throws RemoteException {
        for (int i = 0; i < PEOPLE; ++i) {
            assertFalse(bank.checkPerson("checkPerson" + i, "", "checkPerson" + i));
            assertTrue(bank.createPerson("checkPerson" + i, "", "checkPerson" + i));
            assertTrue(bank.checkPerson("checkPerson" + i, "", "checkPerson" + i));
        }
    }

    @Test
    public void checkRemoteAfterLocal() throws RemoteException {
        bank.createPerson("checkRemoteAfterLocal", "1", "checkRemoteAfterLocal1");

        Person remote = bank.getRemotePerson("checkRemoteAfterLocal1");
        assertNotNull(remote);

        assertTrue(bank.createAccount(remote,  "1"));
        Person local = bank.getLocalPerson("checkRemoteAfterLocal1");
        assertNotNull(local);

        Account localAccount = bank.getAccount(local, "1");
        localAccount.setAmount(localAccount.getAmount() + 100);

        Account remoteAccount = bank.getAccount(remote, "1");
        assertEquals(100, localAccount.getAmount());
        assertEquals(0, remoteAccount.getAmount());
    }

    @Test
    public void checkLocalAfterRemote() throws RemoteException {
        String passport = "CheckLocalAfterRemote1";
        bank.createPerson("checkLocalAfterRemote", "1", passport);
        Person remote = bank.getRemotePerson(passport);

        assertNotNull(remote);

        assertTrue(bank.createAccount(remote,  "1"));
        Account remoteAccount = bank.getAccount(remote, "1");

        Person local2 = bank.getLocalPerson(passport);

        remoteAccount.setAmount(remoteAccount.getAmount() + 100);

        Person local = bank.getLocalPerson(passport);
        assertNotNull(local);

        Account localAccount = bank.getAccount(local, "1");
        Account localAccount2 = bank.getAccount(local2, "1");

        assertEquals(localAccount.getAmount(), remoteAccount.getAmount());
        assertEquals(localAccount2.getAmount() + 100, localAccount.getAmount());
    }

    @Test
    public void checkCreatingAccount() throws RemoteException {
        String passport = "checkCreatingAccount1";
        bank.createPerson("checkCreatingAccount", "1", passport);
        Person remote = bank.getRemotePerson(passport);
        Person local = bank.getLocalPerson(passport);

        bank.createAccount(remote, "2");
        assertNull(bank.getAccount(local, "2"));
        assertEquals(1, bank.getPersonAccounts(remote).size());
        assertNotNull(bank.getAccount(remote, "2"));
        assertNotEquals(bank.getPersonAccounts(local), bank.getPersonAccounts(remote));
    }

    @Test
    public void checkRemoteRemote() throws RemoteException {
        String passport = "checkRemoteRemote1";
        bank.createPerson("checkRemoteRemote", "1", passport);

        Person remote1 = bank.getRemotePerson(passport);
        Person remote2 = bank.getRemotePerson(passport);

        bank.createAccount(remote1, "1");
        bank.createAccount(remote2, "2");

        assertEquals(2, bank.getPersonAccounts(remote1).size());
        assertEquals(bank.getPersonAccounts(remote1).size(), bank.getPersonAccounts(remote2).size());
    }

    @Test
    public void checkLocalLocal() throws RemoteException {
        String passport = "checkLocalLocal1";
        bank.createPerson("checkLocalLocal", "1", passport);

        Person local1 = bank.getLocalPerson(passport);
        Person local2 = bank.getLocalPerson(passport);

        bank.createAccount(local1, "1");
        bank.createAccount(local2, "2");

        Person local3 = bank.getLocalPerson(passport);
        assertEquals(2, bank.getPersonAccounts(local3).size());
        assertEquals(0, bank.getPersonAccounts(local1).size());
        assertEquals(bank.getPersonAccounts(local1).size(), bank.getPersonAccounts(local2).size());
    }
}