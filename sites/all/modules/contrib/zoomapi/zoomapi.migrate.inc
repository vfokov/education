<?php

/**
 * @file
 * Logic to migrate from v1 to v2.
 */

/**
 * Migrate Webhooks.
 */
function zoomapi_migrate_webhooks() {
  // Do not create webhooks v2 if they are not currently enabled for v1.
  if (!variable_get('zoomapi_webhooks_enabled', FALSE)) {
    return;
  }

  // If we do not have the webhooks username/password then do not create
  // webhooks v2.
  $auth_user = variable_get('zoomapi_webhooks_username', FALSE);
  $auth_password = variable_get('zoomapi_webhooks_password', FALSE);

  if (!$auth_user || !$auth_password) {
    return;
  }

  $zoom_client = zoomapi_client();
  $zoom_client->webhooks()->options(['version' => 'v2']);

  $webhook = [
    'url' => url('zoomapi/webhook', ['absolute' => TRUE]),
    'auth_user' => $auth_user,
    'auth_password' => $auth_password,
    'events' => [
      'meeting_started',
      'meeting_ended',
      'meeting_jbh',
      'meeting_join',
      'recording_completed',
      'participant_joined',
      'participant_left',
      'meeting_registered',
      'recording_transcript_completed',
    ],
  ];
  $zoom_client->api('webhook')->create($webhook);
}

/**
 * Migrate Users (populate table).
 */
function zoomapi_migrate_users_batch_operation_populate_table($uid, $data) {
  $realm = zoomapi_realm();
  $created = REQUEST_TIME;
  $changed = REQUEST_TIME;

  $fields = [
    'uid' => $uid,
    'zoom_user_id' => $data['zoomapi_user_id'],
    'zoom_email' => $data['zoom_user_email'],
    'realm' => $realm,
    'created' => $created,
    'changed' => $changed,
  ];

  $query = db_merge('zoomapi_users')
    ->key(['zoom_email' => $fields['zoom_user_email']])
    ->fields($fields)
    ->execute();
}

/**
 * Migrate Users (populate table).
 */
function zoomapi_migrate_users_batch_operation_clean_data($uid, $data) {
  unset($data['zoomapi_user_id']);
  unset($data['zoomapi_user_email']);
  db_update('users')
    ->fields(['data' => $data])
    ->condition('uid', $uid)
    ->execute();
}
